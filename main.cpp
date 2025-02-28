#include <iostream>    // Input/output stream library
#include <iomanip>     // Input/output manipulation library
#include <vector>      // Vector container library
#include <string>      // String library

#include "CSVReader.h" // CSVReader header file

void dijkstra(const Graph<Location>* city, Vertex<Location> *src, Vertex<Location> *dest) {
    if (src == nullptr || dest == nullptr) {
        std::cout << "Invalid initial or destination city choice. Please try again." << std::endl;
        return;
    }

    if (src == dest) {
        std::cout << "Initial city is the same as the destination!" << std::endl;
        return;
    }

    MutablePriorityQueue<Vertex<Location>> pq;

    for (Vertex<Location>* location : city->getVertexSet()) {
        location->setVisited(false);
        location->setPath(nullptr);
        location->setDist(0);
    }
    pq.insert(src);

    while (!pq.empty()) {
        Vertex<Location> *current = pq.extractMin();
        current->setVisited(true);
        if (current->getInfo().getId() == dest->getInfo().getId()) {
            break;
        }

        double fastestTime = std::numeric_limits<double>::max();
        std::wcout << current->getInfo().getStreets().size() << std::endl;
        for (Street *street : current->getInfo().getStreets()) {
            double newDist = current->getDist() + street->getTime(false);
            Vertex<Location> *next = street->getStreet()->getDest();
            if (next->getInfo().isAvailable() && !next->isVisited() && newDist < fastestTime) {
                fastestTime = newDist;
                next->setDist(fastestTime);
                current->setPath(street->getStreet());
                pq.insert(next);
            }
        }
    }
    if (pq.empty()) {
        std::cout << "No path found!" << std::endl;
    } else {
        std::wcout << L"Best Driving Route: ";
        double bestDistance = 0;
        for (Vertex<Location> *location = src; location != dest; location = location->getPath()->getDest()) {
            bestDistance += location->getDist();
            std::wcout << location->getInfo().getId() << " -> ";
        }
        bestDistance += dest->getDist();
        std::wcout << dest->getInfo().getId() << std::endl << L"Best Distance Time: " << bestDistance << std::endl;
    }
}

// Function to print menu options
void printMenuOptions()
{
    std::cout << "Route Planning Analysis Tool Menu:" << std::endl;
    std::cout << "1. Print All Locations" << std::endl;
    std::cout << "2. Exit" << std::endl;
}

// Function to print reports
void printReport(const std::string& reportType, const Graph<Location>* cityGraph) {
    std::cout << reportType << " reports: " << std::endl;

    if (reportType == "Locations") {
        // Ensure sufficient width for each column
        std::wcout << std::setw(15) << std::left << L"Location ID"
                   << std::setw(40) << std::left << L"Location Name"
                   << std::setw(20) << std::left << L"Code"
                   << std::setw(15) << std::left << L"Parking" << std::endl;

        for (Vertex<Location> * location : cityGraph->getVertexSet()) {
            // Print out each field ensuring proper width for wide characters
            std::wcout << std::setw(15) << std::left << location->getInfo().getId()
                       << std::setw(40) << std::left << location->getInfo().getName()
                       << std::setw(20) << std::left << location->getInfo().getCode()
                       << std::setw(15) << std::left << (location->getInfo().hasParking() ? L"Yes" : L"No") << std::endl;
        }
    }
    else {
        std::cout << "Invalid report type." << std::endl;
        return;
    }
}

// Function to display the menu and handle user input
void menu(Graph<Location> *cityGraph)
{
    printMenuOptions();

    bool menuOpen = true;

    while (menuOpen)
    {
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            printReport("Locations", cityGraph);
            printMenuOptions(); // Display the menu again after printing the report
            break;
        case 2: {
            int startingCity, destCity, counter = 0;
            std::cout << "Choose the starting city (Id number):" << std::endl;
            std::cin >> startingCity;
            std::cout << "Choose the destination: (Id number):" << std::endl;
            std::cin >> destCity;
            Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;

            for (Vertex<Location> *location : cityGraph->getVertexSet()) {
                if (location->getInfo().getId() == startingCity) {
                    counter++;
                    startPoint = location;
                }
                if (location->getInfo().getId() == destCity) {
                    counter++;
                    endPoint = location;
                }
                if (counter == 2) {
                    break;
                }
            }

            dijkstra(cityGraph, startPoint, endPoint);
            break;
        }

        case 3:
            std::cout << "Exiting..." << std::endl;
            menuOpen = false; // Exit the menu loop
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

// Main function, entry point of the program
int main()
{
    setlocale(LC_ALL, "pt_PT.UTF-8");
    std::locale loc("pt_PT.UTF-8");
    std::wcout.imbue(loc);

    std::wstring locations_filename = L"./data/Locations.csv";
    std::wstring distances_filename = L"./data/Distances.csv";

    auto *cityGraph = new Graph<Location>();  // Create a new graph for the city

    // Read location data from the CSV file
    CSVReader locationsReader(locations_filename);
    locationsReader.readLocationData(cityGraph);

    // Read distance data from the CSV file
    CSVReader distancesReader(distances_filename);
    distancesReader.readDistanceData(cityGraph);

    menu(cityGraph);  // Call the menu function to display options to the user

    delete cityGraph;  // Clean up dynamically allocated memory

    return 0;
}
