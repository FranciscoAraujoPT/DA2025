#include "Truck.h"

// Default constructor
Truck::Truck() : capacity(0), pallets() {}

Truck::Truck(int capacity, const std::vector<Pallet>& pallets)
    : capacity(capacity), pallets(pallets) {
    // Constructor initializes the truck with the given capacity and pallets
}

int Truck::getCapacity() const {
    return capacity;
}

const std::vector<Pallet>& Truck::getPallets() const {
    return pallets;
}
