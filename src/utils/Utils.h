/**
* @file Utils.h
 * @brief Utility functions for handling user input, interactions with the graph and printing graph information.
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"

/**
 * @namespace Utils
 * @brief Contains utility functions for input handling and graph interaction.
 */
namespace Utils {
    /**
    * @brief Prompts the user for an integer input and validates it.
     *
     * Ensures the input is a valid integer and handles input errors.
     *
     * @param prompt The message to display to the user.
     * @return A valid integer inputted by the user.
    */
    int getValidatedInt(const std::string& prompt);

    /**
     * @brief Allows the user to select start and end locations in the graph.
     *
     * @param cityGraph Pointer to the graph representing the city.
     * @param startPoint Reference to store the selected start vertex.
     * @param endPoint Reference to store the selected end vertex.
     * @return Returns 0 on success, or an error code if selection fails.
     */
    int chooseStartAndEndingCities(Graph<Location>* cityGraph, Vertex<Location> *&startPoint, Vertex<Location> *&endPoint);

    /**
     * @brief Allows the user to specify nodes and segments to avoid in the graph.
     *
     * @param cityGraph Pointer to the graph representing the city.
     * @return Returns 0 on success, or an error code if an error occurs.
     */
    int chooseNodesAndSegmentsToAvoid(Graph<Location>* cityGraph);

    /**
     * @brief Allows the user to choose middle points in the graph.
     *
     * @param cityGraph Pointer to the graph representing the city.
     * @return A vector containing pointers to the selected middle points.
     */
    std::vector<Vertex<Location>*> chooseMiddlePoint(Graph<Location>* cityGraph);

    /**
     * @brief Checks if the start and destination cities are adjacent.
     *
     * @param startCity The starting city vertex.
     * @param destCity The destination city vertex.
     * @return Returns 1 if adjacent, 0 otherwise.
     */
    int checkStartAndEndingCitiesAdjacency(const Vertex<Location> &startCity, const Vertex<Location> &destCity);

    /**
     * @brief Prints a report of the graph based on the specified type.
     *
     * @param reportType Type of report to generate.
     * @param cityGraph Pointer to the graph representing the city.
     */
    void printReport(const std::string& reportType, const Graph<Location>* cityGraph);

    /**
     * @brief Prints the calculated route and its distance.
     *
     * @param path The sequence of vertices representing the route.
     * @param bestDistance The best computed distance for the route.
     */
    void printRoute(const std::vector<Vertex<Location>*>& path, double bestDistance);
}


#endif //UTILS_H
