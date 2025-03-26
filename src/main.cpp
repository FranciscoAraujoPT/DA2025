/**
* @file main.cpp
 * @brief Entry point for the Environment-Friendly Route Planning system.
 *
 * Loads city data and starts the interactive menu-driven application.
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

#include "data_handling/CSVReader.h"
#include "utils/Utils.h"
#include "ui/Menu.h"

/**
 * @brief Entry point of the route planning system.
 *
 * Initializes the city graph from CSV files, loads location and distance data,
 * and launches the user interface through the main menu.
 *
 * @return Exit status of the program.
 */
int main()
{
    setlocale(LC_ALL, "");

    std::string locations_filename = "./data/SmallLocations.csv";
    std::string distances_filename = "./data/SmallDistances.csv";

    auto *cityGraph = new Graph<Location>();  // Create a new graph for the city

    // Read location data from the CSV file
    CSVReader locationsReader(locations_filename);
    locationsReader.readLocationData(cityGraph);

    // Read distance data from the CSV file
    CSVReader distancesReader(distances_filename);
    distancesReader.readDistanceData(cityGraph);

    menu(cityGraph);  // Call the menu function to display options to the user

    delete cityGraph;  // Clean up dynamically allocated memory

    return 0;
}
