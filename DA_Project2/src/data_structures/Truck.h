/**
* @file Truck.h
 * @brief Defines the `Truck` class that represents a delivery truck.
 *
 * This file contains the definition of the `Truck` class. The truck holds information about its capacity
 * and the list of pallets that can be loaded onto it. The `Truck` class provides methods to get these details.
 *
 * @see Truck.cpp for the implementation.
 */

#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include "Pallet.h"

class Truck {

public:
    /**
     * @brief Default constructor for an empty Truck object.
     *
     * Initializes the truck with zero capacity and no pallets.
     */
    Truck();

    /**
     * @brief Constructor to initialize a Truck object with a given capacity and list of pallets.
     *
     * @param capacity The weight capacity of the truck.
     * @param pallets The list of pallets that can be loaded onto the truck.
     */
    Truck(int capacity, const std::vector<Pallet>& pallets);

    /**
     * @brief Returns the weight capacity of the truck.
     *
     * This function returns the maximum weight that the truck can carry. It is used to compare against
     * the total weight of selected pallets to ensure the truck doesn't exceed its capacity.
     *
     * @return The weight capacity of the truck.
     */
    int getCapacity() const;

    /**
     * @brief Returns the list of pallets that can be loaded onto the truck.
     *
     * This function provides access to the list of pallets available to be loaded into the truck. Each
     * pallet has a unique identifier, weight, and profit, and they will be considered for loading based
     * on optimization algorithms.
     *
     * @return The vector of pallets that can be loaded onto the truck.
     */
    const std::vector<Pallet>& getPallets() const;

private:
    int capacity;  ///< The maximum weight capacity of the truck.
    std::vector<Pallet> pallets;  ///< The list of pallets.
};

#endif // TRUCK_H
