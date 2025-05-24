/**
 * @file ILPBranchAndBound.h
 * @brief Defines the interface for solving the knapsack problem using Integer Linear Programming with Branch and Bound.
 *
 * This file declares the function for solving the knapsack problem using a Branch and Bound approach,
 * leveraging LP relaxation for bounding and exploring decision nodes efficiently to find the optimal set of pallets.
 *
 * @see ILPBranchAndBound.cpp for the implementation.
 */

#ifndef ILP_BRANCH_AND_BOUND_H
#define ILP_BRANCH_AND_BOUND_H

#include "../data_structures/Truck.h"

namespace ILPBranchAndBound {
    /**
     * @brief Solves the knapsack problem using Integer Linear Programming with a Branch and Bound strategy.
     *
     * This method applies a Branch and Bound algorithm to determine the subset of pallets that maximizes
     * profit without exceeding the truck's weight capacity. It uses a greedy-based LP relaxation to estimate
     * upper bounds and prunes non-promising branches to optimize the search.
     *
     * @param truck The truck containing a list of pallets and its capacity.
     *
     * @details The method sorts the pallets by profit-to-weight ratio, explores decision nodes in a BFS manner,
     * and updates the best solution found as it traverses the tree. Each node tracks the level of decision,
     * cumulative profit, weight, and selection path.
     *
     * @complexity
     * - Time Complexity: O(2^n) in the worst case, where `n` is the number of pallets (full tree traversal).
     *   However, pruning significantly reduces the number of evaluated nodes in practice.
     * - Space Complexity: O(n) for tracking selection paths per node.
     */
    void solve(const Truck &truck);
};

#endif // ILP_BRANCH_AND_BOUND_H

