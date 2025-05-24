/**
 * @file Utils.h
 * @brief Defines utility functions used across the project.
 *
 * This file declares helper functions for tasks such as input validation, timing, and various other utilities
 * that are commonly used across different parts of the project.
 *
 * @see Utils.cpp for the implementation.
 */

#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include "../data_structures/Truck.h"

/**
 * @brief Timer macro to start the execution timer.
 *
 * This macro starts the execution timer, usually used for measuring the performance of algorithms.
 */
#define START_TIMER auto start = std::chrono::high_resolution_clock::now()

/**
 * @brief Timer macro to stop the execution timer and report the elapsed time.
 *
 * This macro stops the execution timer and reports the elapsed time since the last call to `START_TIMER`.
 * It is typically used to analyze the performance of algorithms.
 *
 * @param algorithmName The name of the algorithm to report the time for.
 */
#define END_TIMER_AND_REPORT(algorithmName) \
auto end = std::chrono::high_resolution_clock::now(); \
std::chrono::duration<double> duration = end - start; \
std::cout << algorithmName << " execution time: " << duration.count() << " seconds." << std::endl;


namespace Utils {

    /**
     * @brief Prompts the user to enter a valid choice between the specified range.
     *
     * This function continuously asks the user for an input until a valid number within the range [min, max]
     * is entered. If the input is invalid (e.g., not an integer or out of range), the function will notify the user
     * and prompt them again.
     *
     * @param min The minimum valid number for the input range.
     * @param max The maximum valid number for the input range.
     *
     * @return The valid input entered by the user, which lies between the `min` and `max` values.
     */
    int getUserChoice(int min, int max);

    /**
     * @brief Prints detailed information about the truck and its pallets.
     *
     * This function displays the truck's capacity and the list of pallets that it contains. For each pallet, it shows
     * the pallet ID, weight, and profit. This is helpful for visualizing the state of the truck and the pallets.
     *
     * @param truck The `Truck` object whose information is to be printed.
     */
    void printTruckInfo(const Truck &truck);

    /**
     * @brief Compares two pallets by their profit-to-weight ratio in descending order.
     *        Useful for greedy or bound-based algorithms where this heuristic improves efficiency.
     *
     * @param a First pallet to compare.
     * @param b Second pallet to compare.
     * @return true if a has a higher ratio than b, false otherwise.
     */
    bool compareByProfitWeightRatio(const Pallet& a, const Pallet& b);
    /**
     * @brief This function takes care of outputting the results to the console.
     *        It displays the total profit, total weight and the pallets chosen by the best solution.
     *
     * @param totalProfit The total profit achieved by the algorithm's solution.
     * @param totalWeight The total weight achieved by the algorithm's solution.
     * @param capacity The total weight capacity of the truck.
     * @param selectedIDs A vector containing the ids of the pallets that were chosen by the algorithm.
     */
    void printResults(int totalProfit, int totalWeight, int capacity, std::vector<int>& selectedIDs);
}

#endif // UTILS_H
