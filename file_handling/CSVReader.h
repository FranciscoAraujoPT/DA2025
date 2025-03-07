//
// Created by francisco-araujo on 3/13/24.
//

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

class CSVReader
{
private:
    std::string filename;
    char delimiter;

public:
    explicit CSVReader(std::string filename, char delimiter = ',');

    void readLocationData(Graph<Location> *cityGraph);
    void readDistanceData(Graph<Location> *cityGraph);
};

#endif // DA_CSVREADER_H
