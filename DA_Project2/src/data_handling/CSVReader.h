/**
* @file CSVReader.h
 * @brief Defines the interface for reading CSV files containing truck and pallet data.
 *
 * This file declares the `CSVReader` class that provides methods to read truck and pallet data from CSV files.
 * The class is responsible for loading the data into appropriate structures for further use.
 *
 * @see CSVReader.cpp for the implementation.
 */

#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include "../data_structures/Truck.h"

class CSVReader {

public:
    /**
     * @brief Constructor to initialize the CSVReader with the base file path and delimiter.
     *
     * This constructor initializes a `CSVReader` object that can read CSV files containing truck and pallet data.
     * It takes the base directory path for the dataset and an optional delimiter to specify how values are separated
     * in the CSV files (default is a comma).
     *
     * @param basePath The base directory path where the CSV files are located.
     * @param delimiter The delimiter used to separate values in the CSV file (default is ',').
     */
     CSVReader(const std::string &basePath, char delimiter = ',');

    /**
     * @brief Reads truck and pallet data from CSV files.
     *
     * This function reads the truck capacity and number of pallets from the truck CSV file and the pallet data
     * (ID, weight, and profit) from the pallet CSV file. It populates a `Truck` object with this data and returns it.
     * If any error occurs (such as the files not existing or being unable to open), an empty `Truck` object is returned.
     *
     * @param datasetId The ID of the dataset to load.
     * @return A `Truck` object containing the data read from the CSV files.
     *         If an error occurs, an empty truck is returned.
     */
    Truck readTruckData(int datasetId);

private:
    std::string basePath; ///< The base directory path to look for the CSV files.
    char delimiter; ///< The character used to separate values in the CSV files (e.g., ',' or ';').
};

#endif // CSVREADER_H
