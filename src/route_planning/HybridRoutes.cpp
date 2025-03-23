/*
Develop functionality to plan routes that combine driving and walking, allowing users to:
    1. Drive the first section of the route and then park the vehicle.
    2. Walk the remaining distance to the destination.
For this part of the project, consider the following assumptions:
    ● The origin and destination cannot be adjacent nodes.                                                                  DONE
    ● The origin and destination cannot be parking nodes.                                                                   DONE
    ● All explored routes must include at least one driving segment and one walking segment.
In addition to the origin and destination, the user provides the following parameter:
    ● Max. Walking Time: Time the user is willing to walk after parking
More requirements:
    ● The best route must include at least one driving segment and one walking segment
    ● The goal is to minimize both driving and walking time
    ● Should there be two or more feasible routes with the same overall minimum travel time,
      you should select the one with the longest walking section
    ● No additional intermediate stop points are allowed in this mode
    ● The user may choose to exclude selected nodes and segments from either the driving or walking sections of travel
    ● If no suitable route is found that satisfies the requirements, indicate which requirements cannot
      be met, i.e., walking time exceeds predefined maximum limit or absence of parking, or both.
*/

#include "../route_planning/HybridRoutes.h"

namespace HybridRoutes {

    void printResults(std::vector<Vertex<Location>*> drivingPath, const std::vector<Vertex<Location>*> &walkingPath, int drivingTime, int walkingTime) {
        std::cout << "DrivingRoute: ";
        Utils::printRoute(drivingPath, drivingTime);
        std::cout << "ParkingNode: " <<  drivingPath.back()->getInfo().getName() << "(" << drivingPath.back()->getInfo().getId() << ")" << std::endl;
        std::cout << "WalkingRoute: ";
        Utils::printRoute(walkingPath, walkingTime);
        std::cout << "TotalTime: " << drivingTime + walkingTime << std::endl;
    }

    void handleEnvFriendlyRoute(Graph<Location>* cityGraph) {
        Vertex<Location>* startPoint = nullptr, *endPoint = nullptr;
        if (Utils::chooseStartAndEndingCities(cityGraph, startPoint, endPoint) == 0) {
            std::cerr << "Error: Didn't find one or both cities." << std::endl;
            return;
        }

        if (Utils::checkStartAndEndingCitiesAdjacency(*startPoint, *endPoint) == 1) {
            std::cerr << "Error: The cities are adjacent and it's not allowed" << std::endl;
            return;
        }

        if (startPoint->getInfo().hasParking()) {
            std::cerr << "Error: The starting point has parking and that is not allowed!" << std::endl;
            return;
        }

        if (endPoint->getInfo().hasParking()) {
            std::cerr << "Error: The destination has parking and that is not allowed!" << std::endl;
            return;
        }

        int maxWalkingTime = Utils::getValidatedInt("Choose the maximum walking time: ");
        Utils::chooseNodesAndSegmentsToAvoid(cityGraph);

        bool isDrivable = false;
        for (auto streets : startPoint->getAdj()) {
            if (streets->getTime(false) != -1 && streets->isAvailable()) {
                isDrivable = true;
                break;
            }
        }
        if (!isDrivable) {
            std::cout << "Message: There are no reachable cities through driving from the start node!" << std::endl;
            return;
        }

        std::vector<Vertex<Location>*> parkingSpots;
        for (Vertex<Location>* location : cityGraph->getVertexSet()) {
            if (location->getInfo().hasParking() && location->getInfo().isAvailable()) {
                parkingSpots.emplace_back(location);
            }
        }

        std::vector<Vertex<Location>*> drivingPath, walkingPath;
        int currentBestTime, walkingTime, drivingTime;
        drivingTime = walkingTime = currentBestTime  = std::numeric_limits<int>::max();
        std::array<std::tuple<std::vector<Vertex<Location>*>, std::vector<Vertex<Location>*>, int, int>, 2> bestAlternatives;
        std::get<2>(bestAlternatives[0]) = std::numeric_limits<int>::max();
        std::get<3>(bestAlternatives[0]) = std::numeric_limits<int>::max();
        std::get<2>(bestAlternatives[1]) = std::numeric_limits<int>::max();
        std::get<3>(bestAlternatives[1]) = std::numeric_limits<int>::max();
        std::tuple<std::vector<Vertex<Location>*>, std::vector<Vertex<Location>*>, int, int> solution;
        std::get<2>(solution) = std::numeric_limits<int>::max();
        std::get<3>(solution) = std::numeric_limits<int>::max();
        bool foundSolution = false;

        for (Vertex<Location>* parkingSpot : parkingSpots) {
            drivingPath = dijkstra(cityGraph, startPoint, parkingSpot, currentBestTime);
            if (drivingPath.empty() || drivingPath.back() != parkingSpot) {
                continue;
            }
            drivingTime = drivingPath.back()->getDist();

            walkingPath = dijkstra(cityGraph, parkingSpot, endPoint, currentBestTime - drivingTime, true);
            if (walkingPath.empty() || walkingPath.back() != endPoint) {
                continue;
            }
            walkingTime = walkingPath.back()->getDist();
            if (walkingTime <= maxWalkingTime && ((static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime) <  static_cast<long long>(std::get<2>(solution)) +  static_cast<long long>(std::get<3>(solution))) || (static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime) == static_cast<long long>(std::get<2>(solution)) +  static_cast<long long>(std::get<3>(solution)) && walkingTime > std::get<3>(solution)))) {
                std::get<0>(solution) = drivingPath;
                std::get<1>(solution) = walkingPath;
                std::get<2>(solution) = drivingTime;
                std::get<3>(solution) = walkingTime;
                currentBestTime = drivingTime + walkingTime;
                foundSolution = true;
            }
            else if (!foundSolution) {
                if (static_cast<long long>(std::get<2>(bestAlternatives[1])) + static_cast<long long>(std::get<3>(bestAlternatives[1])) < static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime) || (static_cast<long long>(std::get<2>(bestAlternatives[1])) + static_cast<long long>(std::get<3>(bestAlternatives[1])) == static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime) && std::get<3>(bestAlternatives[1]) > walkingTime)) {
                   continue;
                }
                std::get<0>(bestAlternatives[1]) = drivingPath;
                std::get<1>(bestAlternatives[1]) = walkingPath;
                std::get<2>(bestAlternatives[1]) = drivingTime;
                std::get<3>(bestAlternatives[1]) = walkingTime;
                if (static_cast<long long>(std::get<2>(bestAlternatives[0])) + static_cast<long long>(std::get<3>(bestAlternatives[0])) > static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime)) {
                    std::swap(bestAlternatives[0], bestAlternatives[1]);
                }
            }

        }


        if (foundSolution) {
            printResults(std::get<0>(solution), std::get<1>(solution), std::get<2>(solution),std::get<3>(solution));
        } else {
            if (drivingTime == std::numeric_limits<int>::max()){
                std::cout << "Message: There are no reachable parking spots through driving!" << std::endl;
            } else if (walkingTime == std::numeric_limits<int>::max()) {
                std::cout << "Message: There are no possible paths to reach the destination walking from the parking spot!" << std::endl;
            } else {
                std::cout << "Message: There are no possible paths to reach the destination walking within the max walking time of " << maxWalkingTime << " min!" << std::endl;
                std::cout << "Suggested Approximated Solutions: " << std::endl;
                std::cout << "Suggestion 1: " << std::endl;
                printResults(std::get<0>(bestAlternatives[0]), std::get<1>(bestAlternatives[0]), std::get<2>(bestAlternatives[0]),std::get<3>(bestAlternatives[0]));
                if (!std::get<0>(bestAlternatives[1]).empty() && !std::get<1>(bestAlternatives[1]).empty()) {
                    std::cout << std::endl << "Suggestion 2: " << std::endl;
                    printResults(std::get<0>(bestAlternatives[1]), std::get<1>(bestAlternatives[1]), std::get<2>(bestAlternatives[1]),std::get<3>(bestAlternatives[1]));
                    std::cout << std::endl;
                } else {
                    std::cout << std::endl << "No suggestion 2 possible found!" << std::endl;
                }
            }
        }
    }
}

