/**
* @file Menu.h
 * @brief Defines the interface for displaying and interacting with the menu.
 *
 * This file declares the function that displays a menu allowing the user to select an algorithm,
 * change datasets, and execute the corresponding actions. It facilitates the interaction with the user.
 *
 * @see Menu.cpp for the implementation.
 */

#ifndef MENU_H
#define MENU_H

#include <string>

namespace Menu {

    /**
     * @brief Displays the menu options and allows the user to interact with the program.
     *
     * This function displays a menu where the user can choose from various options such as:
     * - Changing the dataset
     * - Running different optimization algorithms (Brute Force, Dynamic Programming, Greedy, Integer Linear Programming)
     *
     * The menu continues to run until the user selects the option to exit the program.
     *
     * @param basePath The base path where the dataset files are located. Used to initialize the CSVReader.
     */
    void menu(const std::string &basePath);

    /**
     * @brief Prints the available menu options to the console.
     *
     * This function displays the list of available actions for the user. It includes the option to:
     * - Change the current dataset
     * - Execute various optimization algorithms
     *
     * It also displays the current dataset being used.
     *
     * @param currentDataset The ID of the current dataset being used, which will be displayed in the menu.
     */
    void printMenuOptions(int currentDataset);

}

#endif // MENU_H
