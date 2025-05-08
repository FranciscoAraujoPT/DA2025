//
// Created by macbook on 07/05/2025.
//
#ifndef PALLET_H
#define PALLET_H

class Pallet {
private:
    int id;
    int weight;
    int profit;

public:
    Pallet(int id, int weight, int profit);

    // Getters
    int getId() const;
    int getWeight() const;
    int getProfit() const;

    // Setters
    void setId(int id);
    void setWeight(int weight);
    void setProfit(int profit);
};

#endif // PALLET_H
