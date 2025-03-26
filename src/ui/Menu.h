/**
* @file Menu.h
 * @brief Provides functions for displaying and handling the menu system.
 */

#ifndef MENU_H
#define MENU_H

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../route_planning/HybridRoutes.h"
#include "../route_planning/IndependentRoutePlanning.h"
#include "../route_planning/RestrictedRoutePlanning.h"
#include "../utils/Utils.h"

/**
 * @brief Displays the main menu and handles user interaction.
 *
 * This function presents the menu options to the user and processes their selection.
 *
 * @param cityGraph Pointer to the graph representing the city.
 */
void menu(Graph<Location> *cityGraph);

/**
 * @brief Prints the available menu options.
 *
 * Displays the different choices available for the user in the menu system.
 */
void printMenuOptions();

/**
 * @brief Gets the user's choice within a specified range.
 *
 * Ensures the user's input falls within the given minimum and maximum bounds.
 *
 * @param min The minimum valid choice.
 * @param max The maximum valid choice.
 * @return The valid user-selected choice.
 */
int getUserChoice(int min, int max);

#endif // MENU_H
