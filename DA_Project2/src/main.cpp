/**
* @file main.cpp
 * @brief The entry point for the truck packing optimization program.
 *
 * This file contains the `main` function, which serves as the entry point of the program.
 * It initializes the necessary components and starts the menu interaction where the user can choose
 * from various algorithms to solve the knapsack problem using different approaches.
 *
 * The `main.cpp` file is responsible for setting up the initial dataset and interacting with the user.
 */

#include "ui/Menu.h"

int main() {
    // Set the base path for the datasets (adjust the path as needed)
    std::string basePath = "../datasets/";

    // Run the menu to interact with the user and start the algorithm selection process
    Menu::menu(basePath);

    return 0;
}

