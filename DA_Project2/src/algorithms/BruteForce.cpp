/**
* @file BruteForce.cpp
 * @brief Implements the brute-force approach for solving the knapsack problem.
 *
 * This file contains the implementation of the algorithm that evaluates all subsets of pallets to find
 * the maximum profit achievable for a truck, while respecting the truck's weight capacity.
 *
 * @see BruteForce.h for the interface.
 */

#include "BruteForce.h"
#include <iostream>
#include <vector>
#include "../utils/Utils.h"

using namespace std;

namespace BruteForce {

    void solve(const Truck& truck) {
        START_TIMER;

        const vector<Pallet>& pallets = truck.getPallets();
        unsigned long n = pallets.size();
        int maxProfit = 0;
        int bestWeight = 0;
        vector<int> bestSubset;
        int capacity = truck.getCapacity();

        int totalComb = 1 << n;

        for (int i = 0; i < totalComb; ++i) {
            int totalWeight = 0;
            int totalProfit = 0;
            vector<int> currentSubset;

            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    totalWeight += pallets[j].getWeight();
                    totalProfit += pallets[j].getProfit();
                    currentSubset.push_back(pallets[j].getId());
                }
            }

            if (totalWeight <= capacity && totalProfit > maxProfit) {
                maxProfit = totalProfit;
                bestWeight = totalWeight;
                bestSubset = currentSubset;
            }
        }

        END_TIMER_AND_REPORT("Brute Force")
        // Output
        cout << "Total Profit: " << maxProfit << endl;
        cout << "Total Weight: " << bestWeight << " / " << capacity << "\n";
        cout << "Best Subset of Pallets (by ID): ";
        for (int id : bestSubset) {
            cout << id << " ";
        }
        cout << endl;
    }

}
