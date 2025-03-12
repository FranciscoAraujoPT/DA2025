#include <iostream>      // Input/output stream library
#include <iomanip>       // Input/output manipulation library
#include <vector>        // Vector container library
#include <string>        // String library
#include <unordered_map> // Unordered map library

#include "data_handling/CSVReader.h" // CSVReader header file
#include "utils/Utils.h"
#include "ui/Menu.h"




// Main function, entry point of the program
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
