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
    std::string truckFile = basePath + "/TruckAndPallets_" + (datasetNumber < 10 ? "0" : "") + std::to_string(datasetNumber) + ".csv";
    std::string palletFile = basePath + "/Pallets_" + (datasetNumber < 10 ? "0" : "") + std::to_string(datasetNumber) + ".csv";

    if (!std::filesystem::exists(truckFile) || !std::filesystem::exists(palletFile)) {
        std::cerr << "Error: Dataset " << datasetNumber << " does not exist." << std::endl;
        return {}; // Return an empty truck
    }

    std::ifstream truckStream(truckFile);
    std::ifstream palletStream(palletFile);
    if (!palletStream.is_open() || !truckStream.is_open()) {
        std::cerr << "Error: Failed to open pallet file: " << palletFile << std::endl;
        return {}; // Return an empty truck
    }

    std::string line;
    std::getline(truckStream, line); // Skip header
    std::getline(truckStream, line);
    std::stringstream ss(line);
    std::string capStr, palStr;
    std::getline(ss, capStr, delimiter);
    std::getline(ss, palStr, delimiter);

    int capacity = std::stoi(capStr);
    int numPallets = std::stoi(palStr);

    Truck truck(capacity, numPallets);

    std::getline(palletStream, line); // Skip header
    while (std::getline(palletStream, line)) {
        std::stringstream pss(line);
        std::string idStr, weightStr, profitStr;

        std::getline(pss, idStr, delimiter);
        std::getline(pss, weightStr, delimiter);
        std::getline(pss, profitStr, delimiter);

        int id = std::stoi(idStr);
        int weight = std::stoi(weightStr);
        int profit = std::stoi(profitStr);

        Pallet pallet(id, weight, profit);
        truck.addPallet(pallet);
    }

    return truck;
}
