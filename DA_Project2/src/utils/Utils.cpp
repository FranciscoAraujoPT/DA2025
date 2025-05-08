#include "Utils.h"
#include <limits>
#include <iostream>

namespace Utils {

    int getUserChoice(int min, int max) {
        int choice;
        while (true) {
            std::cin >> choice;  // Read user input
            if (std::cin.fail() || choice < min || choice > max) {
                // If input is invalid or out of range
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            } else {
                // Return valid choice
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return choice;
            }
        }
    }

    void printTruckInfo(const Truck &truck) {
        std::cout << "\n--- Truck Info ---\n";
        std::cout << "Truck Capacity: " << truck.getCapacity() << "\n";
        std::cout << "Number of Pallets: " << truck.getPallets().size() << "\n";

        std::cout << "\n--- Pallets ---\n";
        // Loop through each pallet and print its details
        for (const Pallet &p : truck.getPallets()) {
            std::cout << "Pallet ID: " << p.getId()
                      << ", Weight: " << p.getWeight()
                      << ", Profit: " << p.getProfit() << "\n";
        }
    }

}
