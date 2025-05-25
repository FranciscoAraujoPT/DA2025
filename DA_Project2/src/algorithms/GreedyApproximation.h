/**
* @file GreedyApproximation.h
 * @brief Defines the interface for solving the knapsack problem using a greedy approximation.
 *
 * This file declares the function for solving the knapsack problem using a greedy approximation algorithm.
 * The approach selects pallets based on the highest weight-to-profit ratio and iterates until the truck is full.
 *
 * @see GreedyApproximation.cpp for the implementation.
 */

#ifndef GREEDY_APPROXIMATION_H
#define GREEDY_APPROXIMATION_H

#include "../data_structures/Truck.h"

namespace GreedyApproximation {
    /**
     * @brief Solves the knapsack problem using a greedy approach based on weight-to-profit ratio.
     *
     * This method selects pallets in descending order of their weight-to-profit ratio until the truck's capacity is reached.
     * It is an approximation algorithm that is faster but may not always find the optimal solution.
     *
     * @param truck The truck containing a list of pallets and its capacity.
     *
     * @details The greedy approach is faster but does not always give the optimal solution.
     * It evaluates pallets based on the ratio of their weight to profit and iteratively selects pallets until the truck is full.
     *
     * **Complexity**
     * - Time Complexity: O(n log n) where `n` is the number of pallets (due to sorting).
     * - Space Complexity: O(n) due to the storage of the sorted pallets.
     */
    void solve(const Truck& truck);
}


#endif // GREEDY_APPROXIMATION_H

