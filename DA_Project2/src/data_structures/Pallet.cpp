//
// Created by macbook on 07/05/2025.
//

#include "Pallet.h"

Pallet::Pallet(int id, int weight, int profit)
    : id(id), weight(weight), profit(profit) {}

// Getters
int Pallet::getId() const {
    return id;
}

int Pallet::getWeight() const {
    return weight;
}

int Pallet::getProfit() const {
    return profit;
}

// Setters
void Pallet::setId(int newId) {
    id = newId;
}

void Pallet::setWeight(int newWeight) {
    weight = newWeight;
}

void Pallet::setProfit(int newProfit) {
    profit = newProfit;
}

