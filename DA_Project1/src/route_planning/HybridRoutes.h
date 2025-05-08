/**
* @file HybridRoutes.h
 * @brief Declares functions for planning routes with both walking and driving sections.
 *
 * This module supports planning driving routes that include mandatory stop locations ,avoid user-specified nodes or edges
 * and returns approximate solutions if no valid solution is found
 */

#ifndef HYBRID_ROUTES_H
#define HYBRID_ROUTES_H

#include <vector>
#include <unordered_map>
#include <string>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../algorithm/Dijkstra.h"
#include "../utils/Utils.h"

/**
 * @namespace HybridRoutes
 * @brief Provides functions to plan hybrid (car + walking) routes with an emphasis on environmental friendliness.
 *
 * This namespace includes algorithms that find optimal paths from a starting point to a destination,
 * prioritizing minimal environmental impact by promoting walking for the last portion of the trip.
 */
namespace HybridRoutes {

    /**
     * @brief Finds the best environmentally friendly route that combines driving and walking.
     *
     * This function calculates the best route from a starting point to a destination using a hybrid approach:
     * driving to a nearby parking spot and walking the rest of the way. It prioritizes minimizing total travel time
     * while respecting a maximum walking time constraint.
     *
     * @param cityGraph Pointer to the graph representing the city map with location nodes.
     * @param startPoint Pointer to the vertex where the journey starts.
     * @param endPoint Pointer to the destination vertex.
     * @param parkingSpots List of potential parking spot vertices.
     * @param maxWalkingTime Maximum time (in minutes) the user is willing to walk from a parking spot to the destination.
     */
    void findBestEnvFriendlyRoute(Graph<Location>* cityGraph,
                                   Vertex<Location>* startPoint,
                                   Vertex<Location>* endPoint,
                                   const std::vector<Vertex<Location>*> &parkingSpots,
                                   int maxWalkingTime);

    /**
     * @brief Prompts the user for input and plans an environmentally friendly route.
     *
     * This function is an interactive version of the hybrid routing algorithm. It prompts the user for start, end,
     * and preferences, and then computes and displays the most eco-friendly route combining driving and walking.
     *
     * @param cityGraph Pointer to the graph representing the city map.
     */
    void planEnvFriendlyRoute(Graph<Location>* cityGraph);

}

#endif
