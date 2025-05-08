/**
* @file Pallet.h
 * @brief Defines the `Pallet` class representing a pallet in the knapsack problem.
 *
 * This file contains the definition of the `Pallet` class. Each pallet has a unique identifier, weight,
 * and profit. These are used to determine which pallets can be loaded onto the truck while maximizing
 * the profit within the weight constraint.
 *
 * @see Pallet.cpp for the implementation.
 */

#ifndef PALLET_H
#define PALLET_H

class Pallet {

public:
    /**
     * @brief Constructor to initialize a Pallet object with a given ID, weight, and profit.
     *
     * @param id The unique identifier of the pallet.
     * @param weight The weight of the pallet.
     * @param profit The profit of the pallet.
     */
    Pallet(int id, int weight, int profit);

    /**
     * @brief Returns the ID of the pallet.
     *
     * This function retrieves the unique identifier of the pallet, which is used to track individual pallets
     * during the optimization process.
     *
     * @return The ID of the pallet.
     */
    int getId() const;

    /**
     * @brief Returns the weight of the pallet.
     *
     * This function returns the weight of the pallet, which is a key constraint in the optimization process.
     * The total weight of selected pallets must not exceed the truck's capacity.
     *
     * @return The weight of the pallet.
     */
    int getWeight() const;

    /**
     * @brief Returns the profit of the pallet.
     *
     * This function returns the profit value associated with the pallet. The optimization algorithms aim to
     * maximize the total profit while staying within the weight limit of the truck.
     *
     * @return The profit of the pallet.
     */
    int getProfit() const;

private:
    int id;     ///< The unique identifier for the pallet.
    int weight; ///< The weight of the pallet.
    int profit; ///< The profit associated with the pallet.
};

#endif // PALLET_H
