/**
* @file DynamicProgramming.cpp
 * @brief Implements the dynamic programming approach for solving the knapsack problem.
 *
 * This file contains the implementation of the algorithm that calculates the optimal set of pallets to load
 * into the truck to maximize the profit, while respecting the weight limit of the truck.
 *
 * The dynamic programming approach iterates over all pallets and computes the maximum profit achievable
 * for each capacity from 0 to the truck's maximum weight.
 *
 * @see DynamicProgramming.h for the interface.
 */

#include "DynamicProgramming.h"
#include <iostream>
#include <vector>
#include "../utils/Utils.h"

using namespace std;

namespace DynamicProgramming {

    void solve(const Truck& truck) {
        START_TIMER;

        const vector<Pallet>& pallets = truck.getPallets();
        int capacity = truck.getCapacity();

        // DP array to store the max profit achievable for each capacity
        vector<int> dp(capacity + 1, 0);

        // To store the selected pallets and their total weight
        struct Selection {
            vector<int> ids;
            int totalWeight = 0;
        };

        vector<Selection> selected(capacity + 1);

        // Dynamic programming to find maximum profit
        for (const auto& pallet : pallets) {
            int w = pallet.getWeight();
            int p = pallet.getProfit();
            int id = pallet.getId();

            for (int c = capacity; c >= w; --c) {
                if (dp[c - w] + p > dp[c]) {
                    dp[c] = dp[c - w] + p;
                    selected[c] = selected[c - w]; // Copy previous selection
                    selected[c].ids.push_back(id); // Add current pallet ID
                    selected[c].totalWeight = selected[c - w].totalWeight + w; // Update total weight
                }
            }
        }

        // Find the best capacity used
        int maxProfit = 0;
        int bestCap = 0;
        for (int i = 0; i <= capacity; ++i) {
            if (dp[i] > maxProfit) {
                maxProfit = dp[i];
                bestCap = i;
            }
        }

        END_TIMER_AND_REPORT("Dynamic Programming")

        // Output results
        const auto& bestSelection = selected[bestCap];
        cout << "Total Profit: " << maxProfit << endl;
        cout << "Total Weight: " << bestSelection.totalWeight << " / " << capacity << "\n";
        cout << "Selected Pallets (by ID): ";
        for (int id : bestSelection.ids) {
            cout << id << " ";
        }
        cout << endl;
    }

}