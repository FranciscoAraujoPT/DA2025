// CSVReader.cpp
#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

// Constructor definition
CSVReader::CSVReader(const std::string& basePath, char delimiter)
    : basePath(basePath), delimiter(delimiter) {}

Truck CSVReader::readTruckData(int datasetNumber) {
    // Create file paths for truck and pallet CSV files based on datasetNumber
    std::string truckFile = basePath + "/TruckAndPallets_" + (datasetNumber < 10 ? "0" : "") + std::to_string(datasetNumber) + ".csv";
    std::string palletFile = basePath + "/Pallets_" + (datasetNumber < 10 ? "0" : "") + std::to_string(datasetNumber) + ".csv";

    // Check if both truck and pallet files exist
    if (!std::filesystem::exists(truckFile) || !std::filesystem::exists(palletFile)) {
        std::cerr << "Error: Dataset " << datasetNumber << " does not exist." << std::endl;
        return {}; // Return an empty truck if files don't exist
    }

    // Open the truck and pallet CSV files
    std::ifstream truckStream(truckFile);
    std::ifstream palletStream(palletFile);

    // Check if the files opened successfully
    if (!palletStream.is_open() || !truckStream.is_open()) {
        std::cerr << "Error: Failed to open pallet file: " << palletFile << std::endl;
        return {}; // Return an empty truck if failed to open the files
    }

    // Read the truck data (skip header, read capacity and number of pallets)
    std::string line;
    std::getline(truckStream, line); // Skip header
    std::getline(truckStream, line); // Read data line
    std::stringstream ss(line);
    std::string capStr, palStr;
    std::getline(ss, capStr, delimiter);
    std::getline(ss, palStr, delimiter);

    // Convert capacity and number of pallets to integers
    int capacity = std::stoi(capStr);
    int numPallets = std::stoi(palStr);

    // Create a vector to contain all pallets of the truck
    std::vector<Pallet> pallets;

    // Read pallet data (skip header)
    std::getline(palletStream, line); // Skip header
    while (std::getline(palletStream, line)) {
        std::stringstream pss(line);
        std::string idStr, weightStr, profitStr;

        // Read pallet properties (id, weight, profit)
        std::getline(pss, idStr, delimiter);
        std::getline(pss, weightStr, delimiter);
        std::getline(pss, profitStr, delimiter);

        // Convert the strings to integers
        int id = std::stoi(idStr);
        int weight = std::stoi(weightStr);
        int profit = std::stoi(profitStr);

        // Create a new pallet and add it to the list of pallets to be added to the truck
        Pallet pallet(id, weight, profit);
        pallets.push_back(pallet);
    }

    // Create Truck object with capacity and with a list of pallets objects
    Truck truck(capacity, pallets);

    return truck; // Return the populated truck object
}
