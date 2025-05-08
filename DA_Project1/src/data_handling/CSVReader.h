/**
* @file CSVReader.h
 * @brief Provides functionality to read and parse CSV files.
 *
 * This file contains the CSVReader class, which is responsible for reading data
 * from CSV files and populating graph structures.
 */

#ifndef DA_CSVREADER_H
#define DA_CSVREADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <utility>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"

/**
 * @class CSVReader
 * @brief Reads and processes CSV files to populate graph structures.
 */
class CSVReader
{
private:
    std::string filename; /**< The name of the CSV file to be read. */
    char delimiter; /**< The character used to separate values in the CSV file. */

public:
    /**
     * @brief Constructs a CSVReader object with the given filename and delimiter.
     *
     * @param filename The path to the CSV file.
     * @param delimiter The character used to separate values (default is ',').
     */
    explicit CSVReader(std::string filename, char delimiter = ',');

    /**
     * @brief Reads location data from the CSV file and populates the graph.
     *
     * @param cityGraph Pointer to the graph representing the city.
     */
    void readLocationData(Graph<Location> *cityGraph);


    /**
     * @brief Reads distance data from the CSV file and populates the graph.
     *
     * @param cityGraph Pointer to the graph representing the city.
     */
    void readDistanceData(Graph<Location> *cityGraph);
};

#endif // DA_CSVREADER_H
