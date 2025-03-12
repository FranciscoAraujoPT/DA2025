//
// Created by barroco on 3/12/25.
//

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

#include "HybridRoutes.h"

HybridRoutes::HybridRoutes(Graph<Location>* cityGraph) : graph(cityGraph) {}

void HybridRoutes::findBestHybridRoute(Graph<Location>* city, Vertex<Location>* src, Vertex<Location>* dest, int maxWalkingTime) {
    std::vector<std::vector<Vertex<Location>*>> paths;

    if (!src || !dest) {
        std::cout << "Invalid source or destination!" << std::endl;
        return;
    }
    if (src == dest) {
        std::cout << "Source and destination are the same!" << std::endl;
        return;
    }

    bool isDrivable = false;
    for (auto streets : src->getAdj()) {
        if (streets->getTime(false) != -1 && streets->isAvailable()) {
            isDrivable = true;
            break;
        }
    }
    if (!isDrivable) {
        std::cout << "There are no reachable cities through driving from the start node!" << std::endl;
        return;
    }

    std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>> drivingParentMap;
    std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>> walkingParentMap;
    MutablePriorityQueue<Vertex<Location>> pq;

    auto drivingDistances = computeDrivingDistances(city, src, drivingParentMap);
    auto walkingDistances = computeWalkingDistances(city, dest, maxWalkingTime, walkingParentMap);
    Vertex<Location>* bestParkingSpot = findBestParkingSpot(drivingDistances, walkingDistances, maxWalkingTime);

    if (!bestParkingSpot) {
        std::cout << "No valid parking spot found within constraints" << std::endl;
        return;
    }

    auto drivingRoute = reconstructPath(src, bestParkingSpot, drivingParentMap);
    auto walkingRoute = reconstructPath(dest, bestParkingSpot, walkingParentMap);
    std::ranges::reverse(walkingRoute); // Since we started from the destination, we need to reverse the path
    int bestDrivingTime = static_cast<int>(drivingDistances.find(bestParkingSpot)->second);
    int bestWalkingTime = static_cast<int>(walkingDistances.find(bestParkingSpot)->second);

    printPath(drivingRoute, "DrivingRoute:");
    std::cout << " (" << bestDrivingTime << ")" << std::endl;
    std::cout << "ParkingNode: " << bestParkingSpot->getInfo().getId() << std::endl;
    printPath(walkingRoute, "WalkingRoute:");
    std::cout << " (" << bestWalkingTime << ")" << std::endl;

    std::cout << "TotalTime: " << bestDrivingTime + bestWalkingTime << std::endl;
}

std::unordered_map<Vertex<Location>*, double> HybridRoutes::computeDrivingDistances(const Graph<Location>* city, Vertex<Location>* src, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& drivingParentMap) {
    std::unordered_map<Vertex<Location>*, double> drivingDistances;
    MutablePriorityQueue<Vertex<Location>> pq;

    for (Vertex<Location>* location : city->getVertexSet()) {
        location->setVisited(false);
        location->setDist(std::numeric_limits<double>::infinity());
        location->setQueueIndex(0);
    }

    src->setDist(0);
    pq.insert(src);

    while (!pq.empty()) {
        Vertex<Location>* current = pq.extractMin();
        current->setVisited(true);

        for (Edge<Location>* street : current->getAdj()) {

            if (street->getTime(false) == -1 || !street->isAvailable()) continue;

            Vertex<Location>* next = street->getDest();

            if (next->isVisited() || !next->getInfo().isAvailable()) continue;

            double newDist = current->getDist() + street->getTime(false);

            if (newDist < next->getDist()) {
                next->setDist(newDist);
                drivingParentMap[next].clear();
                drivingParentMap[next].push_back(current);
                if (next->getQueueIndex() == 0) {
                    pq.insert(next);
                }
                else {
                    pq.decreaseKey(next);
                }
            }
            else if (newDist == next->getDist()) {
                drivingParentMap[next].push_back(current);
            }
        }
    }

    // Store only parking spots
    for (Vertex<Location>* location : city->getVertexSet()) {
        if (location->getInfo().hasParking()) {
            drivingDistances[location] = location->getDist();
        }
    }

    return drivingDistances;
}

std::unordered_map<Vertex<Location>*, double> HybridRoutes::computeWalkingDistances(const Graph<Location>* city, Vertex<Location>* dest, int maxWalkingTime, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>> &walkingParentMap) {

    std::unordered_map<Vertex<Location>*, double> walkingDistances;
    MutablePriorityQueue<Vertex<Location>> pq;

    for (Vertex<Location>* location : city->getVertexSet()) {
        location->setVisited(false);
        location->setQueueIndex(0);
        location->setDist(std::numeric_limits<double>::infinity());
    }

    dest->setDist(0);
    pq.insert(dest);

    while (!pq.empty()) {
        Vertex<Location>* current = pq.extractMin();
        current->setVisited(true);

        for (Edge<Location>* street : current->getAdj()) {
            if (!street->isAvailable()) continue;

            Vertex<Location>* next = street->getDest();

            if (next->isVisited() || !next->getInfo().isAvailable()) continue;

            double newDist = current->getDist() + street->getTime(true);

            if (newDist > maxWalkingTime) continue;

            if (newDist < next->getDist()) {
                next->setDist(newDist);
                walkingDistances[next] = newDist;
                walkingParentMap[next].clear();
                walkingParentMap[next].push_back(current);
                if (next->getQueueIndex() == 0) {
                    pq.insert(next);
                }
                else {
                    pq.decreaseKey(next);
                }
            }
            else if (newDist == next->getDist()) {
                walkingParentMap[next].push_back(current);
            }
        }
    }

    return walkingDistances;
}

Vertex<Location>* HybridRoutes::findBestParkingSpot(std::unordered_map<Vertex<Location>*, double> &drivingDistances, std::unordered_map<Vertex<Location>*, double> &walkingDistances, int maxWalkingTime) {

    Vertex<Location>* bestParkingSpot = nullptr;
    double bestTotalTime = std::numeric_limits<double>::infinity();
    double longestWalkingTime = 0;

    for (auto& [parkingSpot, drivingTime] : drivingDistances) {
        if (!walkingDistances.contains(parkingSpot)) continue;

        double walkingTime = walkingDistances[parkingSpot];
        if (walkingTime > maxWalkingTime) continue;

        double totalTime = drivingTime + walkingTime;

        if (totalTime < bestTotalTime || (totalTime == bestTotalTime && walkingTime > longestWalkingTime)) {
            bestTotalTime = totalTime;
            longestWalkingTime = walkingTime;
            bestParkingSpot = parkingSpot;
        }
    }

    return bestParkingSpot;
}

std::vector<Vertex<Location>*> HybridRoutes::reconstructPath(Vertex<Location>* start, Vertex<Location>* end, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& parentMap) {
    // Base case: if start and end are the same, return a vector with just start
    if (start == end) {
        return {start};
    }

    // If end is not in parentMap or has no parents, return empty path
    if (!parentMap.contains(end) || parentMap[end].empty()) {
        std::cout << "No path is available to " << end->getInfo().getName() << " because it has no parents." << std::endl;
        return {};
    }

    for (auto parent : parentMap[end]) {
        auto path = reconstructPath(start, parent, parentMap);

        if (!path.empty()) {
            path.push_back(end);
            return path;
        }
    }

    std::cout << "No valid path found to " << end->getInfo().getName() << std::endl;
    return {};
}

void HybridRoutes::printPath(const std::vector<Vertex<Location>*>& path, const std::string& label) {
    int index = 0;
    const int lastIndex = path.size() - 1;

    std::cout << label << ": ";
    for (auto location : path) {
        if (index == lastIndex) {
            std::cout << location->getInfo().getId();
            break;
        }
        std::cout << location->getInfo().getId() << " -> ";
        index++;
    }
}