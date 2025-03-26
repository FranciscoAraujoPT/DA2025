/**
* @file RestrictedRoutePlanning.h
 * @brief Declares functions for planning routes with restricted segments or conditions.
 *
 * This module supports planning driving routes that include mandatory stop locations
 * and avoid user-specified nodes or edges.
 */

#ifndef RESTRICTED_ROUTE_PLANNING_H
#define RESTRICTED_ROUTE_PLANNING_H

#include <vector>
#include <iostream>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../algorithm/Dijkstra.h"
#include "../utils/Utils.h"

/**
 * @namespace RestrictedRoutePlanning
 * @brief Contains functions for planning routes with specific constraints like stop points and restricted areas.
 */
namespace RestrictedRoutePlanning {

    /**
     * @brief Interactively plans a route with restrictions and mandatory stops.
     *
     * This function allows the user to choose cities to avoid and required middle points,
     * then computes and displays the optimal driving route under those constraints.
     *
     * @param cityGraph Pointer to the graph representing the city.
     */
    void planRestrictedRoute(Graph<Location>* cityGraph);

    /**
     * @brief Finds the best route from start to end passing through specified intermediate locations.
     *
     * @param cityGraph Pointer to the graph representing the city.
     * @param start Pointer to the starting vertex.
     * @param end Pointer to the destination vertex.
     * @param stopLocations A list of intermediate stop points.
     * @param bestDistance Reference to store the total distance of the computed path.
     * @return A vector of vertices representing the best route covering all specified stops.
     */
    std::vector<Vertex<Location>*> findMultiStopRoute(Graph<Location>* cityGraph, Vertex<Location>* start, Vertex<Location>* end, std::vector<Vertex<Location>*>& stopLocations, double& bestDistance);
}

#endif // RESTRICTED_ROUTE_PLANNING_H
