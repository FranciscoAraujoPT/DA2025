// CSVReader.h
#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>
#include "../data_structures/Truck.h"

class CSVReader {
private:
    std::string basePath;
    char delimiter;

public:
    // Constructor declaration
    CSVReader(const std::string& basePath, char delimiter = ',');

    // Function to read truck data
    Truck readTruckData(int datasetNumber);
};

#endif // CSV_READER_H
