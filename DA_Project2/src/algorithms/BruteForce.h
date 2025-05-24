/**
* @file ILPBranchAndBound.h
 * @brief Defines the interface for solving the knapsack problem using Integer Linear Programming with Branch and Bound.
 *
 * This file declares the function for solving the knapsack problem using a Branch and Bound approach,
 * leveraging LP relaxation for bounding and exploring decision nodes efficiently to find the optimal set of pallets.
 *
 * @see ILPBranchAndBound.cpp for the implementation.
 */

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "../data_structures/Truck.h"

namespace BruteForce {

    /**
     * @brief Solves the knapsack problem using an exhaustive (brute-force) approach.
     *
     * This method evaluates all possible subsets of pallets to find the maximum profit that can be achieved
     * while staying within the truck's weight capacity.
     *
     * @param truck The truck containing a list of pallets and its capacity.
     *
     * @details The brute-force approach generates all subsets of pallets and checks their total weight and profit.
     * It is guaranteed to find the optimal solution but has poor performance with large datasets.
     *
     * @complexity
     * - Time Complexity: O(2^n) where `n` is the number of pallets (since all subsets are evaluated).
     * - Space Complexity: O(n) due to the storage required for the pallet selection.
     */
    void solve(const Truck& truck);
}

#endif // BRUTE_FORCE_H
