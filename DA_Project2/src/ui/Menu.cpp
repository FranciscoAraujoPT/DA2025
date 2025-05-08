#include "Menu.h"
#include "../data_structures/Truck.h"
#include "../algorithms/BruteForce.h"
#include "../algorithms/DynamicProgramming.h"
#include "../algorithms/GreedyApproximation.h"
#include "../algorithms/ILPOrHybrid.h"
#include "../utils/Utils.h"
#include "../data_handling/CSVReader.h"

void menu(const std::string &basePath) {
    bool menuOpen = true;
    int currentDataset = 1; // Default dataset

    CSVReader reader(basePath); // Initialize CSVReader with the basePath

    // Read data for the selected dataset
    Truck truck = reader.readTruckData(currentDataset); // Initialize with first dataset

    while (menuOpen) {
        printMenuOptions(currentDataset);

        int choice = Utils::getUserChoice(0, 5); // Change max value to 5 for dataset changing

        switch (choice) {
            case 1: {
                // Change dataset
                std::cout << "Enter new dataset number (e.g., 1, 2, ...), 0 to go back: ";
                int auxCurrentDataset = Utils::getUserChoice(0, 99); // Assuming datasets are 01 to 99
                if (auxCurrentDataset == 0) {
                    break;
                }
                // Try loading the new dataset
                Truck auxTruck = reader.readTruckData(auxCurrentDataset); // Load new dataset
                if (auxTruck.getCapacity() != 0) {  // Check if truck was successfully loaded (no capacity = error)
                    currentDataset = auxCurrentDataset;
                    truck = auxTruck;
                    std::cout << "Dataset " << currentDataset << " loaded successfully.\n";
                } else {
                    std::cout << "Failed to load dataset " << auxCurrentDataset << ". Please try again.\n";
                }
                break;
            }

            case 2: {
                std::cout << "\n[Brute Force Solver]\n";
                BruteForce::solve(truck);
                break;
            }

            case 3: {
                std::cout << "\n[Dynamic Programming Solver]\n";
                DynamicProgramming::solve(truck);
                break;
            }

            case 4: {
                std::cout << "\n[Greedy Solver]\n";
                GreedyApproximation::solve(truck);
                break;
            }

            case 5: {
                std::cout << "\n[Integer Linear Programming Solver]\n";
                ILPOrHybrid::solve(truck);
                break;
            }

            case 0: {
                std::cout << "Exiting...\n";
                menuOpen = false;
                break;
            }

            default:
                std::cerr << "Unexpected menu choice\n";
        }
    }
}

void printMenuOptions(int currentDataset) {
    std::cout << "\n===== Delivery Truck Packing Optimization =====\n";
    std::cout << "Current Dataset: " << currentDataset << "\n";
    std::cout << "1. Change Dataset\n";
    std::cout << "2. Brute Force Solver (T2.1)\n";
    std::cout << "3. Dynamic Programming Solver (T2.2)\n";
    std::cout << "4. Greedy Approximation (T2.3)\n";
    std::cout << "5. Integer Linear Programming (T2.4)\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}
