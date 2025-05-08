#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "../data_structures/Truck.h"

namespace Utils {
    /**
     * @brief Safely gets a user integer input between min and max.
     */
    int getUserChoice(int min, int max);

    /**
     * @brief Prints the contents of the truck and its pallets.
     */
    void printTruckInfo(const Truck &truck);
}

#endif // UTILS_H
