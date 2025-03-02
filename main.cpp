#include <iostream>    // Input/output stream library
#include <iomanip>     // Input/output manipulation library
#include <vector>      // Vector container library
#include <string>      // String library

#include "file_handling/CSVReader.h" // CSVReader header file


std::vector<Vertex<Location>*> dijkstra(const Graph<Location>* city, Vertex<Location>* src, Vertex<Location>* dest) {
    std::vector<Vertex<Location>*> path;
    if (!src || !dest) {
        std::cout << "Invalid source or destination!" << std::endl;
        return path;
    }

    if (src == dest) {
        std::cout << "Source and destination are the same!" << std::endl;
        return path;
    }

    MutablePriorityQueue<Vertex<Location>> pq;

    // **Initialize distances and paths**
    for (Vertex<Location>* location : city->getVertexSet()) {
        location->setVisited(false);
        location->setPath(nullptr);
        location->setDist(std::numeric_limits<double>::infinity());
        location->setQueueIndex(0);
    }

    src->setDist(0);
    pq.insert(src);

    while (!pq.empty()) {
        Vertex<Location>* current = pq.extractMin();
        current->setVisited(true);

        if (current == dest) break;  // Stop early if destination is reached

        for (Street* street : current->getInfo().getStreets()) {
            //std::wcout << street->getStreet()->getOrig()->getInfo().getName() << " " << street->getTime(false) << " " << street->getStreet()->getDest()->getInfo().getName() << std::endl;
            if (street->getTime(false) == -1) {
                continue;
            }
            Vertex<Location>* next = street->getStreet()->getDest();

            if (next->isVisited() || !next->getInfo().isAvailable()) {
                continue;  // Skip visited nodes
            }

            double newDist = current->getDist() + street->getTime(false);  // Edge weight = travel time

            if (newDist < next->getDist()) {
                next->setDist(newDist);
                next->setPath(street->getStreet());  // Store the edge, not the vertex
                if (next->getQueueIndex() == 0) {  // If not in the queue, insert it
                    pq.insert(next);
                } else {  // If already in the queue, update it
                    pq.decreaseKey(next);
                }
            }
        }
    }

    // **If no path was found**
    if (dest->getDist() == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found!" << std::endl;
        return path;
    }

    // **Reconstruct path using edges**

    Vertex<Location>* v = dest;

    while (v != src) {
        Edge<Location>* edge = v->getPath();
        if (!edge) {
            std::cout << "Path reconstruction failed!" << std::endl;
            return path;
        }
        path.push_back(v);
        v = edge->getOrig();  // Move to previous vertex
    }
    path.push_back(src);
    std::reverse(path.begin(), path.end());

    // **Print results**
    for (size_t i = 0; i < path.size(); ++i) {


    }
    return path;
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
            int startingCity, destCity;
            std::cout << "Choose the starting city (Id number):" << std::endl;
            std::cin >> startingCity;
            std::cout << "Choose the destination: (Id number):" << std::endl;
            std::cin >> destCity;
            Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;

            for (Vertex<Location> *location : cityGraph->getVertexSet()) {
                if (location->getInfo().getId() == startingCity) {
                    startPoint = location;
                }
                if (location->getInfo().getId() == destCity) {
                    endPoint = location;
                }
                Location aux = location->getInfo();
                aux.setAvailability(true);
                location->setInfo(aux);
            }
            std::wcout << L"Best Driving Route: ";
            std::vector<Vertex<Location>*> path = dijkstra(cityGraph, startPoint, endPoint);
            for (size_t i = 0; i < path.size(); ++i) {
                if (path[i] != startPoint && path[i] != endPoint) {
                    Location aux = path[i]->getInfo();
                    aux.setAvailability(false);
                    path[i]->setInfo(aux);
                }
                std::wcout << path[i]->getInfo().getName();
                if (i < path.size() - 1) {
                    std::wcout << L" -> ";
                } else {
                    std::wcout << L"\t Best Distance Time: " << path[i]->getDist() << std::endl;
                }
            }
            std::wcout << L"Best Alternative Driving Route: ";
            path = dijkstra(cityGraph, startPoint, endPoint);
            for (size_t i = 0; i < path.size(); ++i) {
                std::wcout << path[i]->getInfo().getName();
                if (i < path.size() - 1) {
                    std::wcout << L" -> ";
                } else {
                    std::wcout << L"\t Best Alternative Distance Time: " << path[i]->getDist() << std::endl;
                }
            }
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

    std::wstring locations_filename = L"./data/SmallLocations.csv";
    std::wstring distances_filename = L"./data/SmallDistances.csv";

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
