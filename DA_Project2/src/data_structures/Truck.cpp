//
// Created by macbook on 07/05/2025.
//

#include "Truck.h"

Truck::Truck(int capacity, int numPallets)
    : capacity(capacity), numPallets(numPallets) {}

// Getters
int Truck::getCapacity() const {
    return capacity;
}

int Truck::getNumPallets() const {
    return numPallets;
}

const std::vector<Pallet>& Truck::getPallets() const {
    return pallets;
}

// Setters
void Truck::setCapacity(int newCapacity) {
    capacity = newCapacity;
}

void Truck::setNumPallets(int newNumPallets) {
    numPallets = newNumPallets;
}

// Add pallet
void Truck::addPallet(const Pallet& pallet) {
    pallets.push_back(pallet);
}
