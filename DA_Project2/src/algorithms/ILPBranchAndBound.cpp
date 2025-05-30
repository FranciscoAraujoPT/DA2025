/**
* @file ILPBranchAndBound.cpp
 * @brief Implements the Branch and Bound strategy for solving the knapsack problem using Integer Linear Programming.
 *
 * This file contains the implementation of the algorithm that determines the optimal set of pallets to load into
 * a truck to maximize profit while respecting the weight limit. It leverages a bounding technique based on the LP
 * relaxation of the problem to prune non-promising solution branches.
 *
 * The approach sorts pallets by profit-to-weight ratio and explores decisions in a breadth-first manner,
 * maintaining the best found solution.
 *
 * @see ILPBranchAndBound.h for the interface.
 */

#include "ILPBranchAndBound.h"
#include "../utils/Utils.h"
#include <iostream>
#include <queue>
#include <vector>

namespace ILPBranchAndBound {

    /**
     * @brief Represents a node in the Branch and Bound decision tree.
     *
     * Each node tracks the current decision level, cumulative weight and profit, upper bound estimate,
     * and the IDs of selected pallets leading to this node.
     */
    struct Node {
        int level;                     ///< The index of the current pallet being considered.
        int bound;                     ///< Upper bound on the best possible profit from this node.
        int profit;                    ///< Current accumulated profit.
        double weight;                ///< Current accumulated weight.
        std::vector<int> selectedIDs; ///< List of IDs for pallets selected up to this node.
    };

    /**
     * @brief Calculates the upper bound of profit from a given node using LP-relaxation.
     *
     * This function estimates the best possible profit that can be obtained starting from the current node.
     * It greedily adds pallets to the capacity until the truck is full or the next pallet would exceed the capacity.
     * If a pallet can't fully fit, a fractional part of its profit is added to represent an optimistic upper bound.
     *
     * @param node The current decision node in the Branch and Bound tree.
     * @param truckCapacity The maximum allowable weight of the truck.
     * @param pallets The list of all available pallets sorted by profit-to-weight ratio.
     *
     * @return An integer representing the estimated maximum profit achievable from this node.
     */
    int getUpperBound(const Node & node, int truckCapacity, const std::vector<Pallet> & pallets) {

        // If the current node's weight exceeds capacity, no further profit can be added
        if (node.weight >= truckCapacity) {
            return 0;
        }

        int profitBound = node.profit;           // Start bound with current node's profit
        int index = node.level + 1;              // Start evaluating from the next pallet
        int totalWeight = node.weight;           // Accumulate total weight

        // Add full pallets while they fit within the remaining truck capacity
        while ((index < pallets.size()) && (totalWeight + pallets[index].getWeight() <= truckCapacity)) {
            totalWeight += pallets[index].getWeight();
            profitBound += pallets[index].getProfit();
            index++;
        }

        // If there's remaining capacity, add a fractional pallet's profit as an optimistic estimate
        if (index < pallets.size()) {
            profitBound += (truckCapacity - totalWeight) * pallets[index].getProfit() / pallets[index].getWeight();
        }

        return profitBound;
    }

    void solve(const Truck &truck) {

        START_TIMER;

        std::vector<Pallet> pallets = truck.getPallets(); // Retrieve the list of pallets
        std::vector<int> selectedIDs; // To track IDs of selected pallets
        std::queue<Node> queue; // BFS queue for Branch and Bound nodes
        int totalProfit = 0; // Best profit found so far
        int totalWeight = 0; // Weight of the best found solution
        const int capacity = truck.getCapacity(); // Truck's maximum capacity
        Node currentNode, bestNode;

        // Sort pallets by profit-to-weight ratio (greedy heuristic)
        sort(pallets.begin(), pallets.end(), Utils::compareByProfitWeightRatio);

        // Initialize root node
        currentNode.level = -1;
        currentNode.profit = currentNode.weight = 0;
        currentNode.selectedIDs = {};
        queue.push(currentNode);

        // Start Branch and Bound traversal
        while (!queue.empty()) {
            currentNode = queue.front();
            queue.pop();

            // First node setup
            if (currentNode.level == -1) {
                bestNode.level = 0;
            }

            // Reached a leaf node
            if (currentNode.level == pallets.size() - 1) {
                continue;
            }

            // Include current pallet
            bestNode.level = currentNode.level + 1;
            bestNode.weight = currentNode.weight + pallets[bestNode.level].getWeight();
            bestNode.profit = currentNode.profit + pallets[bestNode.level].getProfit();
            bestNode.selectedIDs = currentNode.selectedIDs;
            bestNode.selectedIDs.push_back(pallets[bestNode.level].getId());

            // Update best profit if valid
            if (bestNode.weight <= capacity && bestNode.profit > totalProfit) {
                totalProfit = bestNode.profit;
                totalWeight = bestNode.weight;
                selectedIDs = bestNode.selectedIDs;
            }

            // Check if this path is worth exploring
            bestNode.bound = getUpperBound(bestNode, capacity, pallets);
            if (bestNode.bound > totalProfit) {
                queue.push(bestNode); // Only push this node if it could lead to a better solution
            }

            // Exclude current pallet
            Node excludeNode = currentNode;
            excludeNode.level = currentNode.level + 1;
            excludeNode.bound = getUpperBound(excludeNode, capacity, pallets);
            if (excludeNode.bound > totalProfit) {
                queue.push(excludeNode); // Also could lead to a better solution
            }
        }

        END_TIMER_AND_REPORT("ILP Branch & Bound");
        Utils::printResults(totalProfit, totalWeight, capacity, selectedIDs); // Output final results
    }
};
