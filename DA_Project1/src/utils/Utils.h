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
    * @brief Prompts the user to choose the dataset to use.
    *
    *
    * @return A pair representing the location and distance files paths.
    */
    std::pair<std::string, std::string> chooseDatasetFiles();

    /**
     * @brief Gets the user's choice within a specified range.
     *
     * Ensures the user's input falls within the given minimum and maximum bounds.
     *
     * @param min The minimum valid choice.
     * @param max The maximum valid choice.
     * @return The valid user-selected choice.
     */
    int getUserChoice(int min, int max);

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
     * @brief Counts the number of accented (non-ASCII) characters in a UTF-8 encoded string.
     *
     * This function scans through a UTF-8 encoded string and counts the number of
     * non-ASCII characters (e.g., accented letters like ç, é, ã, etc.). It handles
     * multibyte characters according to UTF-8 encoding rules.
     *
     * Note: Each multibyte character (2–4 bytes) is counted as a single character.
     *
     * @param text The UTF-8 encoded string to analyze.
     * @return int The number of non-ASCII (accented or special) characters in the string.
     */
    int countSpecialChars(const std::string& text);

    /**
     * @brief Prints a report of the graph based on the specified type.
     *
     * @param cityGraph Pointer to the graph representing the city.
     */
    void printReport(const Graph<Location>* cityGraph);

    /**
     * @brief Prints the calculated route and its distance.
     *
     * @param path The sequence of vertices representing the route.
     * @param bestDistance The best computed distance for the route.
     */
    void printRoute(const std::vector<Vertex<Location>*>& path, double bestDistance);
}


#endif //UTILS_H
