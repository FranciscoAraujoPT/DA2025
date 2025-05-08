#include "Utils.h"
#include <limits>

namespace Utils {

    int getUserChoice(int min, int max) {
        int choice;
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || choice < min || choice > max) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            } else {
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
        for (const Pallet &p : truck.getPallets()) {
            std::cout << "Pallet ID: " << p.getId()
                      << ", Weight: " << p.getWeight()
                      << ", Profit: " << p.getProfit() << "\n";
        }
    }

}
