/**
 * @file HybridRoutes.h
 * @brief Provides environment-friendly and hybrid route planning functionalities.
 *
 * This file declares functions for computing optimal hybrid routes combining walking and driving,
 * taking into account user constraints such as maximum walking time.
 */

#ifndef HYBRID_ROUTES_H
#define HYBRID_ROUTES_H

#include <vector>
#include <unordered_map>
#include <string>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../utils/Utils.h"

/**
 * @namespace HybridRoutes
 * @brief Contains algorithms for hybrid route planning combining walking and driving.
 */
namespace HybridRoutes {

    /**
     * @brief Handles user interaction to compute an environment-friendly route.
     * @param cityGraph Pointer to the city graph.
     */
    void handleEnvFriendlyRoute(Graph<Location>* cityGraph);

    /**
     * @brief Computes and displays the best hybrid route from source to destination.
     * @param cityGraph Pointer to the city graph.
     * @param src Starting location.
     * @param dest Destination location.
     * @param maxWalkingTime Maximum time the user is willing to walk.
     */
    void findBestHybridRoute(Graph<Location>* cityGraph, Vertex<Location>* src, Vertex<Location>* dest, int maxWalkingTime);

    /**
     * @brief Computes driving distances from a source vertex using Dijkstra's algorithm.
     * @param city Pointer to the city graph.
     * @param src Source vertex.
     * @param drivingParentMap Map to store parent paths for reconstruction.
     * @return A map of each reachable vertex to its driving distance from the source.
     */
    std::unordered_map<Vertex<Location>*, double> computeDrivingDistances(const Graph<Location>* city, Vertex<Location>* src, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& drivingParentMap);

    /**
     * @brief Computes walking distances to a destination vertex considering a time limit.
     * @param city Pointer to the city graph.
     * @param dest Destination vertex.
     * @param maxWalkingTime Maximum allowed walking time.
     * @param walkingParentMap Map to store parent paths for reconstruction.
     * @return A map of each reachable vertex to its walking distance to the destination.
     */
    std::unordered_map<Vertex<Location>*, double> computeWalkingDistances(const Graph<Location>* city, Vertex<Location>* dest, int maxWalkingTime, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& walkingParentMap);

    /**
     * @brief Finds the best parking spot by balancing driving and walking distances.
     * @param drivingDistances Map of driving distances from source.
     * @param walkingDistances Map of walking distances to destination.
     * @param maxWalkingTime Maximum allowed walking time.
     * @return Pointer to the best vertex representing a parking spot.
     */
    Vertex<Location>* findBestParkingSpot(std::unordered_map<Vertex<Location>*, double>& drivingDistances, std::unordered_map<Vertex<Location>*, double>& walkingDistances, int maxWalkingTime);

    /**
     * @brief Reconstructs a path from start to end using a parent map.
     * @param start Starting vertex.
     * @param end Ending vertex.
     * @param parentMap A map of each vertex to its list of parent vertices.
     * @return A vector representing the reconstructed path.
     */
    std::vector<Vertex<Location>*> reconstructPath(Vertex<Location>* start, Vertex<Location>* end, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& parentMap);
}

#endif // HYBRID_ROUTES_H
