/**
* DA - Delivery Truck Pallet Packing Optimization
 *
 * @section intro_sec Introduction
 * This project solves a delivery truck pallet packing problem using combinatorial optimization algorithms.
 * It reads pallet and truck data from CSV files and applies various strategies to maximize profit
 * while respecting truck weight capacity constraints.
 *
 * Algorithms implemented:
 * - Brute Force (Exhaustive Search)
 * - Dynamic Programming
 * - Greedy Approximation
 * - Integer Linear Programming using Branch and Bound
 *
 * @section usage_sec How to Use
 * Run the application and use the interactive menu to:
 * - Select a dataset
 * - Choose an algorithm to apply
 * - View the optimal or approximate packing solution with profits and selected pallets
 *
 * @section structure_sec Code Structure
 * - `main.cpp`: Launches the application and handles user interaction
 * - `Truck`, `Pallet`: Core data structures
 * - `Utils`: Helper functions (input handling, output formatting)
 * - Algorithm namespaces in respective `.cpp`/`.h` pairs
 *
 * @section docs_sec Documentation
 * Use the navigation tabs (Files, Classes, Namespaces) to browse the documentation.
 * Each algorithm is documented in its corresponding header and implementation files.
 */

#include "ui/Menu.h"

int main() {
    // Set the base path for the datasets (adjust the path as needed)
    std::string basePath = "../datasets/";

    // Run the menu to interact with the user and start the algorithm selection process
    Menu::menu(basePath);

    return 0;
}

