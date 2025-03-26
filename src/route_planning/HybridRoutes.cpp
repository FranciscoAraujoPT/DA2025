#include "../route_planning/HybridRoutes.h"

#define PATH_FOUND 0
#define APPROXIMATED_PATH_FOUND 1
#define NO_PATH_FOUND_TO_PARKING 2
#define NO_PATH_FOUND_TO_DESTINATION 3

namespace HybridRoutes {
    /**
     * @brief Prints the results of the driving and walking segments of a hybrid route.
     *
     * Displays the driving route, parking node, walking route, and the total travel time.
     *
     * @param drivingPath Vector of vertices representing the driving path.
     * @param walkingPath Vector of vertices representing the walking path.
     * @param drivingTime Total time (in minutes) of the driving segment.
     * @param walkingTime Total time (in minutes) of the walking segment.
     */
    void printPathResults(std::vector<Vertex<Location>*> drivingPath, const std::vector<Vertex<Location>*> &walkingPath, int drivingTime, int walkingTime) {
        std::cout << "DrivingRoute: ";
        Utils::printRoute(drivingPath, drivingTime);
        std::cout << "ParkingNode: " <<  drivingPath.back()->getInfo().getName() << "(" << drivingPath.back()->getInfo().getId() << ")" << std::endl;
        std::cout << "WalkingRoute: ";
        Utils::printRoute(walkingPath, walkingTime);
        std::cout << "TotalTime: " << drivingTime + walkingTime << std::endl;
    }
    /**
     * @brief Prints the best found solution or fallback alternatives based on the result status.
     *
     * Depending on whether an exact path or an approximated solution was found, this function formats and prints
     * the result(s), including fallback suggestions if needed.
     *
     * @param foundSolution Status code indicating which solution was found.
     * @param solution Primary route solution (driving + walking + times).
     * @param alternativeSolution Optional second-best solution for approximation fallback.
     * @param maxWalkingTime Maximum walking time allowed for the user.
     */
    void printResults(int foundSolution, std::tuple<std::vector<Vertex<Location>*>, std::vector<Vertex<Location>*>, int, int> solution, const std::tuple<std::vector<Vertex<Location>*>, std::vector<Vertex<Location>*>, int, int> &alternativeSolution, int maxWalkingTime) {
        switch (foundSolution) {
            case PATH_FOUND:
                printPathResults(std::get<0>(solution), std::get<1>(solution), std::get<2>(solution),std::get<3>(solution));
                break;
            case APPROXIMATED_PATH_FOUND:
                std::cout << "Message: There are no possible paths to reach the destination walking within the max walking time of " << maxWalkingTime << " min!" << std::endl;
                std::cout << "Suggested Approximated Solutions: " << std::endl;
                std::cout << "Suggestion 1: " << std::endl;
                printPathResults(std::get<0>(solution), std::get<1>(solution), std::get<2>(solution),std::get<3>(solution));
                if (!std::get<0>(alternativeSolution).empty() && !std::get<1>(alternativeSolution).empty()) {
                    std::cout << std::endl << "Suggestion 2: " << std::endl;
                    printPathResults(std::get<0>(alternativeSolution), std::get<1>(alternativeSolution), std::get<2>(alternativeSolution),std::get<3>(alternativeSolution));
                    std::cout << std::endl;
                } else {
                    std::cout << std::endl << "No suggestion 2 possible found!" << std::endl;
                }
                break;
            case NO_PATH_FOUND_TO_PARKING:
                std::cout << "Message: There are no reachable parking spots through driving!" << std::endl;
                break;
            case NO_PATH_FOUND_TO_DESTINATION:
                std::cout << "Message: There are no possible paths to reach the destination walking from the parking spot!" << std::endl;
                break;
            default:
                std::cout << "Message: Unknown error occur when printing the results." << std::endl;
                break;
        }
    }
    /**
     * @brief Finds all available parking spots in the graph.
     *
     * Iterates over all vertices in the graph and selects those that are marked as parking spots and currently available.
     *
     * @param cityGraph Pointer to the city graph.
     * @return Vector of vertices that represent valid parking spots.
     */
    std::vector<Vertex<Location>*> findAllParkingSpots(Graph<Location>* cityGraph) {
        std::vector<Vertex<Location>*> parkingSpots;
        for (Vertex<Location>* location : cityGraph->getVertexSet()) {
            if (location->getInfo().hasParking() && location->getInfo().isAvailable()) {
                parkingSpots.emplace_back(location);
            }
        }

        return parkingSpots;
    }

    /**
     * @brief Checks if a vertex has any adjacent drivable edges.
     *
     * Used to determine whether the current location can be reached or exited by driving.
     *
     * @param startPoint Pointer to the vertex to check.
     * @return True if the vertex has at least one drivable and available edge, false otherwise.
     */
    bool adjacentDrivingEdges(Vertex<Location>* startPoint) {
        bool isDrivable = false;
        for (auto streets : startPoint->getAdj()) {
            if (streets->getTime(false) != -1 && streets->isAvailable()) {
                isDrivable = true;
                break;
            }
        }
        return isDrivable;
    }

    void findBestEnvFriendlyRoute(Graph<Location>* cityGraph, Vertex<Location>* startPoint, Vertex<Location>* endPoint, const std::vector<Vertex<Location>*> &parkingSpots, int maxWalkingTime) {
        std::vector<Vertex<Location>*> drivingPath, walkingPath;
        int currentBestTime, walkingTime, drivingTime;
        std::tuple<std::vector<Vertex<Location>*>, std::vector<Vertex<Location>*>, int, int> solution, alternativeSolution;

        // Initializing Values
        drivingTime = walkingTime = currentBestTime  = std::numeric_limits<int>::max();
        std::get<0>(alternativeSolution) = {};
        std::get<1>(alternativeSolution) = {};
        std::get<2>(alternativeSolution) = std::numeric_limits<int>::max();
        std::get<3>(alternativeSolution) = std::numeric_limits<int>::max();
        std::get<0>(solution) = {};
        std::get<1>(solution) = {};
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
                if (static_cast<long long>(std::get<2>(alternativeSolution)) + static_cast<long long>(std::get<3>(alternativeSolution)) < static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime) || (static_cast<long long>(std::get<2>(alternativeSolution)) + static_cast<long long>(std::get<3>(alternativeSolution)) == static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime) && std::get<3>(alternativeSolution) > walkingTime)) {
                   continue;
                }
                std::get<0>(alternativeSolution) = drivingPath;
                std::get<1>(alternativeSolution) = walkingPath;
                std::get<2>(alternativeSolution) = drivingTime;
                std::get<3>(alternativeSolution) = walkingTime;
                if (static_cast<long long>(std::get<2>(solution)) + static_cast<long long>(std::get<3>(solution)) > static_cast<long long>(drivingTime) + static_cast<long long>(walkingTime)) {
                    std::swap(solution, alternativeSolution);
                }
            }
        }

        int currentSolution;
        if (foundSolution) {
            currentSolution = PATH_FOUND;
        } else {
            if (drivingTime == std::numeric_limits<int>::max()){
                currentSolution = NO_PATH_FOUND_TO_PARKING;
            } else if (walkingTime == std::numeric_limits<int>::max()) {
                currentSolution = NO_PATH_FOUND_TO_DESTINATION;
            } else {
                currentSolution = APPROXIMATED_PATH_FOUND;
            }
        }
        printResults(currentSolution, solution, alternativeSolution, maxWalkingTime);
    }
    void planEnvFriendlyRoute(Graph<Location>* cityGraph) {
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

        if (!adjacentDrivingEdges(startPoint)) {
            std::cout << "Message: There are no reachable cities through driving from the start node!" << std::endl;
            return;
        }

        std::vector<Vertex<Location>*> parkingSpots = findAllParkingSpots(cityGraph);
        findBestEnvFriendlyRoute(cityGraph, startPoint, endPoint, parkingSpots, maxWalkingTime);
    }
}

