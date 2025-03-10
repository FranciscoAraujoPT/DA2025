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
        path.push_back(src);
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

        for (Edge<Location>* street : current->getAdj()) {
            if (street->getTime(false) == -1 || !street->isAvailable()) {
                continue;
            }
            Vertex<Location>* next = street->getDest();

            if (next->isVisited() || !next->getInfo().isAvailable()) {
                continue;  // Skip visited nodes
            }

            double newDist = current->getDist() + street->getTime(false);

            if (newDist < next->getDist()) {
                next->setDist(newDist);
                next->setPath(street);  // Store the edge, not the vertex
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

int chooseNodesAndSegmentsToAvoid(Graph<Location>* cityGraph) {
    std::string input;

    std::cout << "Avoid nodes (Id number):" << std::endl;
    std::getline(std::cin, input);
    std::istringstream stream(input); // Convert the line into a stream

    int num, found = 0;;
    std::vector<int> avoidNodes;

    while (stream >> num) {  // Extract numbers from the stream
        avoidNodes.push_back(num);
    }

    for (int id : avoidNodes) {
        for (Vertex<Location> * location : cityGraph->getVertexSet()) {
            if (location->getInfo().getId() == id) {
                Location aux = location->getInfo();
                aux.setAvailability(false);
                location->setInfo(aux);
                found++;
                break;
            }
        }
        if (found != 1) {
            std::cerr << "Error: Didn't find location by id = " << id << "." << std::endl;
        }
        found = 0;
    }

    std::vector<std::pair<int, int>> avoidSegments;

    std::cout << "Avoid Segments (Id number, Id number):" << std::endl;
    std::getline(std::cin, input);
    std::istringstream stream2(input);
    std::string pairStr;

    while (stream2 >> pairStr) {  // Read each "x,y" pair
        std::replace(pairStr.begin(), pairStr.end(), ',', ' '); // Replace ',' with space
        std::istringstream pairStream(pairStr);
        int first, second;

        if (pairStream >> first >> second) {  // Extract two numbers
            avoidSegments.emplace_back(first, second);
        }
    }

    found = 0;

    for (const auto& pair : avoidSegments) {
        for (Vertex<Location> * location : cityGraph->getVertexSet()) {
            if (location->getInfo().getId() == pair.first || location->getInfo().getId() == pair.second) {
                Location aux = location->getInfo();
                for (Edge<Location>* s : location->getAdj()) {
                    if (s->getDest()->getInfo().getId() == pair.first || s->getDest()->getInfo().getId() == pair.second) {
                        s->setAvailability(false);
                        location->setInfo(aux);
                        found++;
                        break;
                    }
                }
            }
            if (found == 2) {
                break;
            }
        }
        if (found != 2) {
            std::cerr << "Error: Didn't found street with locations with the id = (" << pair.first << "," << pair.second << ")." << std::endl;
        }
        found = 0;
    }
    return  0;
}

int chooseStartAndEndingCities(Graph<Location>* cityGraph, Vertex<Location> *&startPoint, Vertex<Location> *&endPoint) {
    int startingCity, destCity;
    std::cout << "Choose the starting city (Id number):" << std::endl;
    std::cin >> startingCity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Choose the destination: (Id number):" << std::endl;
    std::cin >> destCity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


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

    if (startPoint && endPoint) {
        return 1;
    }

    return 0;
}

std::vector<Vertex<Location>*> chooseMiddlePoint(Graph<Location>* cityGraph) {
    std::string input;
    std::cout << "Choose the locations to make stops, in order, during path (Id number): " << std::endl;
    std::getline(std::cin, input);
    std::istringstream stream(input); // Convert the line into a stream


    int num, found = 0;;
    std::vector<int> stopNodesId;

    while (stream >> num) {  // Extract numbers from the stream
        stopNodesId.push_back(num);
    }
    std::vector<Vertex<Location>*> stopLocations;
    for (int id : stopNodesId) {
        for (Vertex<Location> * location : cityGraph->getVertexSet()) {
            if (location->getInfo().getId() == id) {
                stopLocations.emplace_back(location);
                found = 1;
                break;
            }
        }
        if (found != 1) {
            std::cerr << "Error: Didn't find location by id = " << id << "." << std::endl;
        }
        found = 0;
    }

    return stopLocations;
}

// Function to print menu options
void printMenuOptions()
{
    std::cout << "Route Planning Analysis Tool Menu:" << std::endl;
    std::cout << "1. Print All Locations" << std::endl;
    std::cout << "2. Independent Route Planning" << std::endl;
    std::cout << "3. Restricted Route Planning" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

// Function to print reports
void printReport(const std::string& reportType, const Graph<Location>* cityGraph) {
    std::cout << reportType << " reports: " << std::endl;

    if (reportType == "Locations") {
        // Ensure sufficient width for each column
        std::cout << std::setw(15) << std::left << "Location ID"
                   << std::setw(40) << std::left << "Location Name"
                   << std::setw(20) << std::left << "Code"
                   << std::setw(15) << std::left << "Parking" << std::endl;

        for (Vertex<Location> * location : cityGraph->getVertexSet()) {
            // Print out each field ensuring proper width for wide characters
            std::cout << std::setw(15) << std::left << location->getInfo().getId()
                       << std::setw(40) << std::left << location->getInfo().getName()
                       << std::setw(20) << std::left << location->getInfo().getCode()
                       << std::setw(15) << std::left << (location->getInfo().hasParking() ? "Yes" : "No") << std::endl;
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
    bool menuOpen = true;

    while (menuOpen)
    {
        printMenuOptions();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice)
        {
        case 1: {
            printReport("Locations", cityGraph);
            break;
        }

        case 2: {
            Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;
            if (chooseStartAndEndingCities(cityGraph, startPoint, endPoint)) {
                std::cout << "Best Driving Route: ";
                std::vector<Vertex<Location>*> path = dijkstra(cityGraph, startPoint, endPoint);
                for (size_t i = 0; i < path.size(); ++i) {
                    if (path[i] != startPoint && path[i] != endPoint) {
                        Location aux = path[i]->getInfo();
                        aux.setAvailability(false);
                        path[i]->setInfo(aux);
                    }
                    std::cout << path[i]->getInfo().getName();
                    std::cout << "(" << path[i]->getInfo().getId() << ")";
                    if (i < path.size() - 1) {
                        std::cout << " -> ";
                    } else {
                        std::cout << "\t Best Time: " << path[i]->getDist() << std::endl;
                    }
                }
                std::cout << "Best Alternative Driving Route: ";
                path = dijkstra(cityGraph, startPoint, endPoint);
                for (size_t i = 0; i < path.size(); ++i) {
                    std::cout << path[i]->getInfo().getName();
                    std::cout << "(" << path[i]->getInfo().getId() << ")";
                    if (i < path.size() - 1) {
                        std::cout << " -> ";
                    } else {
                        std::cout << "\t Best Alternative Time: " << path[i]->getDist() << std::endl;
                    }
                }
            } else {
                std::cerr << "Error: Didn't find one or both cities" << std::endl;
            }
            break;
        }

        case 3: {
            Vertex<Location> *startPoint, *endPoint;
            if (chooseStartAndEndingCities(cityGraph, startPoint, endPoint)) {
                chooseNodesAndSegmentsToAvoid(cityGraph);
                std::vector<Vertex<Location>*> stopLocations = chooseMiddlePoint(cityGraph);
                Vertex<Location>* start = startPoint;
                std::vector<Vertex<Location>*> totalPath;
                Vertex<Location>* end = endPoint;
                double bestDistance = 0;
                bool success = true;
                for (Vertex<Location>* location : stopLocations) {
                    end = location;
                    std::vector<Vertex<Location>*> path = dijkstra(cityGraph, start, end);
                    if (path.size() > 0) {
                        bestDistance = bestDistance + path[path.size() - 1]->getDist();
                        totalPath.insert(totalPath.end(), path.begin(), path.end()-1);
                    } else {
                        success = false;
                        break;
                    }
                    start = location;
                }
                if (success) {
                    std::vector<Vertex<Location>*> path = dijkstra(cityGraph, start, endPoint);
                     if (path.size() > 0) {
                         bestDistance = bestDistance + path[path.size() - 1]->getDist();
                         totalPath.insert(totalPath.end(), path.begin(), path.end());
                         for (size_t i = 0; i < totalPath.size(); ++i) {
                             std::cout << totalPath[i]->getInfo().getName();
                             std::cout << "(" << totalPath[i]->getInfo().getId() << ")";

                             if (i < totalPath.size() - 1) {
                                 std::cout << " -> ";
                             } else {
                                 std::cout << "\t Best Time: " << bestDistance << std::endl;
                             }
                         }
                    } else {
                        std::cerr << "Error: Didn't find a path from " << start->getInfo().getName() << " to " << endPoint->getInfo().getName() << "." << std::endl;

                    }
                } else {
                    std::cerr << "Error: Didn't find a path from " << start->getInfo().getName() << " to " << end->getInfo().getName() << "." << std::endl;
                }



            } else {
                std::cerr << "Error: Didn't find one or both cities" << std::endl;
            }
            break;
        }

        case 4:
            std::cout << "Exiting..." << std::endl;
            menuOpen = false; // Exit the menu loop
            break;

        default:
            std::cerr << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

// Main function, entry point of the program
int main()
{
    setlocale(LC_ALL, "");

    std::string locations_filename = "./data/SmallLocations.csv";
    std::string distances_filename = "./data/SmallDistances.csv";

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
