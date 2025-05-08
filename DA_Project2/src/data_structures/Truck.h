//
// Created by macbook on 07/05/2025.
//

#ifndef TRUCK_H
#define TRUCK_H

#include <vector>
#include "Pallet.h"

class Truck {
private:
    int capacity;
    int numPallets;
    std::vector<Pallet> pallets;

public:
    // Default constructor for an empty truck
    Truck() : capacity(0), numPallets(0) {}

    Truck(int capacity, int numPallets);

    // Getters
    int getCapacity() const;
    int getNumPallets() const;
    const std::vector<Pallet>& getPallets() const;

    // Setters
    void setCapacity(int newCapacity);
    void setNumPallets(int newNumPallets);

    // Method to add a pallet
    void addPallet(const Pallet& pallet);
};

#endif // TRUCK_H
