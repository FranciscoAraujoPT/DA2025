//
// Created by barroco on 3/12/25.
//

#include "Menu.h"

void menu(Graph<Location> *cityGraph)
{
    bool menuOpen = true;

    while (menuOpen)
    {
        printMenuOptions();
        int choice = getUserChoice(0,5);
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

        case 4: {
                Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;
                int maxWalkingTime = 0;
                const int outcome = chooseStartAndEndingCitiesEnvFriendly(cityGraph, startPoint, endPoint, maxWalkingTime);

                if (outcome == 0) {
                    std::cerr << "Error: Didn't find one or both cities" << std::endl;
                    break;
                }
                if (outcome == 2) {
                    std::cerr << "Error: One of the cities has parking and it's not allowed" << std::endl;
                    break;
                }
                if (outcome == 3) {
                    std::cerr << "Error: The cities are adjacent and it's not allowed" << std::endl;
                    break;
                }

                // Choose segments to avoid
                // Choose cities to avoid
                HybridRoutes hybridRoutes(cityGraph);
                hybridRoutes.findBestHybridRoute(cityGraph, startPoint, endPoint, maxWalkingTime);

                break;
        }


       case 5: {
            std::cout << "Exiting..." << std::endl;
            menuOpen = false; // Exit the menu loop
            break;
       }


       default: {
            std::cerr << "Invalid choice. Please try again." << std::endl;
            break;
       }
        }
    }
}

void printMenuOptions()
{
    std::cout << "Route Planning Analysis Tool Menu:" << std::endl;
    std::cout << "1. Print All Locations" << std::endl;
    std::cout << "2. Independent Route Planning" << std::endl;
    std::cout << "3. Restricted Route Planning" << std::endl;
    std::cout << "4. Environmentally-Friendly Route Planning" << std::endl;
    std::cout << "5. Approximate Solution" << std::endl;
    std::cout << "0. Exit" << std::endl;
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