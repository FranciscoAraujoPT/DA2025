#include "Pallet.h"

Pallet::Pallet(int id, int weight, int profit)
    : id(id), weight(weight), profit(profit) {
    // Constructor initializes the pallet with a unique ID, weight, and profit
}

int Pallet::getId() const {
    return id;
}

int Pallet::getWeight() const {
    return weight;
}

int Pallet::getProfit() const {
    return profit;
}
