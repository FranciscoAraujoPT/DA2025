/**
* @file DynamicProgramming.h
 * @brief Defines the interface for solving the knapsack problem using dynamic programming.
 *
 * This file declares the function for solving the 0/1 knapsack problem using dynamic programming.
 * The algorithm computes the maximum profit that can be achieved while staying within the truck's capacity.
 *
 * @see DynamicProgramming.cpp for the implementation.
 */

#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include "../data_structures/Truck.h"

namespace DynamicProgramming {

    /**
     * @brief Solves the knapsack problem using dynamic programming.
     *
     * This method computes the maximum profit achievable for the given truck's capacity by selecting pallets.
     * It also tracks the total weight of the selected pallets and the corresponding IDs.
     *
     * @param truck The truck containing a list of pallets and its capacity.
     *
     * @details The dynamic programming approach uses a bottom-up technique to compute the maximum profit for
     * each capacity. It iterates through each pallet and updates the profit and weight values accordingly.
     *
     * @note The solution utilizes a 1D DP array for efficiency. The maximum capacity is the largest index
     * in the array.
     *
     * **Complexity**
     * - Time Complexity: O(n * W) where `n` is the number of pallets and `W` is the capacity of the truck.
     * - Space Complexity: O(W) where `W` is the capacity of the truck (due to the DP array and selection tracking).
     */
    void solve(const Truck& truck);
}

#endif // DYNAMIC_PROGRAMMING_H
