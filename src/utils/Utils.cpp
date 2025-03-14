#include "Utils.h"

#include <sstream>

namespace Utils {
    int getValidatedInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a valid number." << std::endl;
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }

    int chooseStartAndEndingCities(Graph<Location>* cityGraph, Vertex<Location> *&startPoint, Vertex<Location> *&endPoint) {
        int startingCity = getValidatedInt("Choose the starting city (Id number): ");
        int destCity = getValidatedInt("Choose the destination (Id number): ");

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

    int checkStartAndEndingCitiesAdjacency(const Vertex<Location> &startCity, const Vertex<Location> &destCity) {
        int flag = 0;
        for (auto location : startCity.getAdj()) {
            if (location->getDest()->getInfo().getId() == destCity.getInfo().getId())
                flag = 1;
        }
        return flag;
    }

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

    void printRoute(const std::vector<Vertex<Location>*>& path, double bestDistance) {
        if (path.empty()) {
            std::cerr << "Error: No valid route found." << std::endl;
            return;
        }

        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->getInfo().getName() << "(" << path[i]->getInfo().getId() << ")";
            if (i < path.size() - 1) {
                std::cout << " -> ";
            } else {
                std::cout << "\t Best Time: " << bestDistance << std::endl;
            }
        }
    }
}