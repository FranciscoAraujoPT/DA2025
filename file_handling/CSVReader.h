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
#include "../data_structures/Location.h"

class CSVReader
{
private:
    std::wstring filename;
    wchar_t delimiter;

public:
    explicit CSVReader(std::wstring filename, wchar_t delimiter = ',');

    void readLocationData(Graph<Location> cityGraph);
    void readDistanceData(Graph<Location> cityGraph);
};

#endif // DA_CSVREADER_H
