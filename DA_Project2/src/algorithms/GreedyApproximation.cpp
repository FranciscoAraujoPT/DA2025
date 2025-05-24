/**
* @file GreedyApproximation.cpp
 * @brief Implements the greedy approximation approach for solving the knapsack problem.
 *
 * This file contains the implementation of the algorithm that uses a greedy approach based on the
 * weight-to-profit ratio to select pallets. It provides a fast but approximate solution to the problem.
 *
 * @see GreedyApproximation.h for the interface.
 */

#include "GreedyApproximation.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../utils/Utils.h"

using namespace std;

namespace GreedyApproximation {
    void solve(const Truck& truck) {
        START_TIMER;

        vector<Pallet> pallets = truck.getPallets();
        int capacity = truck.getCapacity();

        // Sort pallets by decreasing profit-to-weight ratio
        sort(pallets.begin(), pallets.end(), Utils::compareByProfitWeightRatio);

        int totalWeight = 0;
        int totalProfit = 0;
        vector<int> selectedIDs;

        for (const Pallet& pallet : pallets) {
            if (totalWeight + pallet.getWeight() <= capacity) {
                totalWeight += pallet.getWeight();
                totalProfit += pallet.getProfit();
                selectedIDs.push_back(pallet.getId());
            }
        }

        END_TIMER_AND_REPORT("Greedy Approximation");
        Utils::printResults(totalProfit, totalWeight, capacity, selectedIDs);

    }
}
