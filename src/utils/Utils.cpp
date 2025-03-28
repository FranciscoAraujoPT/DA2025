#include "Utils.h"

#include <sstream>

namespace Utils {
    std::pair<std::string, std::string> chooseDatasetFiles() {
        std::cout << "Choose the Dataset:" << std::endl;
        std::cout << "1 - Small (SmallLocations.csv / SmallDistances.csv)" << std::endl;
        std::cout << "2 - Large (Locations.csv / Distances.csv)" << std::endl;

        int option = Utils::getUserChoice(1, 2);

        if (option == 1)
            return {"./data/SmallLocations.csv", "./data/SmallDistances.csv"};
        else
            return {"./data/Locations.csv", "./data/Distances.csv"};
    }

    int getUserChoice(int min, int max) {
        int choice;
        while (true) {
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (std::cin.fail() || choice < min || choice > max) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return choice;
            }
        }
    }

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

    int countSpecialChars(const std::string& text) {
        int count = 0;

        for (size_t i = 0; i < text.size(); ) {
            unsigned char c = static_cast<unsigned char>(text[i]);

            if ((c & 0x80) == 0) {
                // ASCII (1 byte)
                i += 1;
            } else if ((c & 0xE0) == 0xC0) {
                // Likely a 2-byte UTF-8 character: é, ç, ã, etc.
                count++;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                // 3-byte character
                count++;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                // 4-byte character (emoji, symbols)
                count++;
                i += 4;
            } else {
                // Fallback
                i += 1;
            }
        }

        return count;
    }

    void printReport(const Graph<Location> *cityGraph) {
        std::cout << "Location reports:" << std::endl;

        constexpr int idWidth = 12;
        constexpr int nameWidth = 35;
        constexpr int codeWidth = 20;
        constexpr int parkingWidth = 8;

        std::cout << std::left
                << std::setw(idWidth) << "Location ID"
                << std::setw(nameWidth) << "Location Name"
                << std::setw(codeWidth) << "Code"
                << std::setw(parkingWidth) << "Parking"
                << std::endl;

        std::cout << std::string(idWidth + nameWidth + codeWidth + parkingWidth + 1, '-') << std::endl;

        for (Vertex<Location> *location: cityGraph->getVertexSet()) {
            const auto &loc = location->getInfo();
            const std::string &name = loc.getName();

            int adjustedNameWidth = nameWidth + countSpecialChars(name);
            std::cout << std::left
                    << std::setw(idWidth) << loc.getId()
                    << std::setw(adjustedNameWidth) << name
                    << std::setw(codeWidth) << loc.getCode()
                    << std::setw(parkingWidth) << (loc.hasParking() ? "Yes" : "No")
                    << std::endl;
        }

        std::cout << "Road reports:" << std::endl;

        constexpr int fromWidth = 35;
        constexpr int toWidth = 35;
        constexpr int walkTimeWidth = 15;
        constexpr int driveTimeWidth = 15;

        std::cout << std::left
                << std::setw(fromWidth) << "From"
                << std::setw(toWidth) << "To"
                << std::setw(walkTimeWidth) << "Walking Time"
                << std::setw(driveTimeWidth) << "Driving Time"
                << std::endl;

        std::cout << std::string(fromWidth + toWidth + walkTimeWidth + driveTimeWidth, '-') << std::endl;

        for (Vertex<Location> *vertex: cityGraph->getVertexSet()) {
            for (Edge<Location> *edge: vertex->getAdj()) {
                const std::string fromName = vertex->getInfo().getName();
                const std::string toName = edge->getDest()->getInfo().getName();
                const int adjustedFromWidth = fromWidth + countSpecialChars(fromName);
                const int adjustedToWidth = toWidth + +countSpecialChars(toName);
                const int drivingTime = static_cast<int>(edge->getTime(false));
                const std::string drivingTimeString = (drivingTime == -1) ? "X" : std::to_string(drivingTime);

                std::cout << std::left
                        << std::setw(adjustedFromWidth) << fromName
                        << std::setw(adjustedToWidth) << toName
                        << std::setw(walkTimeWidth) << edge->getTime(true)
                        << std::setw(driveTimeWidth) << drivingTimeString
                        << std::endl;
            }
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