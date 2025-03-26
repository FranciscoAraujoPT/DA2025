/**
* @file IndependentRoutePlanning.h
 * @brief Declares functions for planning independent driving routes.
 *
 * This module includes functionality for selecting start and end points and finding the best driving route between them.
 */

#ifndef INDEPENDENT_ROUTE_PLANNING_H
#define INDEPENDENT_ROUTE_PLANNING_H

#include <vector>
#include <iostream>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../algorithm/Dijkstra.h"
#include "../utils/Utils.h"

/**
 * @namespace IndependentRoutePlanning
 * @brief Contains functions for planning independent driving routes.
 */
namespace IndependentRoutePlanning {

    /**
     * @brief Interactively plans a driving route using user input.
     *
     * This function prompts the user to choose a start and end location
     * and prints the best and alternative driving routes between them.
     *
     * @param cityGraph Pointer to the graph representing the city.
     */
    void planDrivingRoute(Graph<Location>* cityGraph);

    /**
     * @brief Finds the best driving route between two vertices.
     *
     * Computes the shortest path using Dijkstra's algorithm and returns it as a list of vertices.
     *
     * @param cityGraph Pointer to the graph representing the city.
     * @param start Pointer to the starting vertex.
     * @param end Pointer to the destination vertex.
     * @return A vector of vertices representing the best driving route.
     */
    std::vector<Vertex<Location>*> findBestDrivingRoute(Graph<Location>* cityGraph, Vertex<Location>* start, Vertex<Location>* end);
}

#endif // INDEPENDENT_ROUTE_PLANNING_H