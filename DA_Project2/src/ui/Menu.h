#ifndef MENU_H
#define MENU_H

#include <iostream>

/**
 * @brief Displays the main menu and allows dataset selection.
 */
void menu(const std::string &basePath);

/**
 * @brief Prints the available algorithm options along with dataset information.
 */
void printMenuOptions(int currentDataset);

#endif // MENU_H
