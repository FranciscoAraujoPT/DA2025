#include "HybridRoutes.h"

namespace HybridRoutes {

    void handleEnvFriendlyRoute(Graph<Location>* cityGraph) {
        Vertex<Location>* startPoint = nullptr, *endPoint = nullptr;
        int maxWalkingTime = 0;
        if (Utils::chooseStartAndEndingCities(cityGraph, startPoint, endPoint) == 0) {
            std::cerr << "Error: Didn't find one or both cities or the cities have parking and it's not allowed." << std::endl;
            return;
        }

        if (Utils::checkStartAndEndingCitiesAdjacency(*startPoint, *endPoint) == 1) {
            std::cerr << "Error: The cities are adjacent and it's not allowed" << std::endl;
            return;
        }

        maxWalkingTime = Utils::getValidatedInt("Choose the maximum walking time: ");

        findBestHybridRoute(cityGraph, startPoint, endPoint, maxWalkingTime);
    }

    void findBestHybridRoute(Graph<Location>* city, Vertex<Location>* src, Vertex<Location>* dest, int maxWalkingTime) {
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

        std::cout << "Choose Driving Restrictions:" << std::endl;
        Utils::chooseNodesAndSegmentsToAvoid(city);
        auto drivingDistances = computeDrivingDistances(city, src, drivingParentMap);

        std::cout << "Choose Walking Restrictions:" << std::endl;
        Utils::chooseNodesAndSegmentsToAvoid(city);
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

        std::cout << "DrivingRoute: ";
        Utils::printRoute(drivingRoute, bestDrivingTime);
        std::cout << "ParkingNode: " << bestParkingSpot->getInfo().getId() << std::endl;
        std::cout << "WalkingRoute: ";
        Utils::printRoute(walkingRoute, bestWalkingTime);
        std::cout << "TotalTime: " << bestDrivingTime + bestWalkingTime << std::endl;
    }

    std::unordered_map<Vertex<Location>*, double> computeDrivingDistances(const Graph<Location>* city, Vertex<Location>* src, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& drivingParentMap) {
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

    std::unordered_map<Vertex<Location>*, double> computeWalkingDistances(const Graph<Location>* city, Vertex<Location>* dest, int maxWalkingTime, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>> &walkingParentMap) {

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

    Vertex<Location>* findBestParkingSpot(std::unordered_map<Vertex<Location>*, double> &drivingDistances, std::unordered_map<Vertex<Location>*, double> &walkingDistances, int maxWalkingTime) {

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

    std::vector<Vertex<Location>*> reconstructPath(Vertex<Location>* start, Vertex<Location>* end, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& parentMap) {
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

}

