#include "CSVReader.h"

CSVReader::CSVReader(std::wstring filename, wchar_t delimiter) : filename(std::move(filename)), delimiter(delimiter) {}

void CSVReader::readLocationData(Graph<Location> *cityGraph)
{
    std::wifstream file(filename); // Use wide file stream
    if (!file.is_open())
    {
        std::wcerr << L"Error: Unable to open file " << filename << std::endl;
        return;
    }

    file.imbue(std::locale("pt_PT.UTF-8"));
    // Skip the header line
    std::wstring header;
    std::getline(file, header);

    // Read CSV data
    std::wstring line;
    while (std::getline(file, line))
    {
        std::wstringstream ss(line); // Use wide stringstream
        std::wstring locationName, locationId, code, parking;
        int id, parkingValue;
        // Assuming the last two columns are empty and ignored
        if (std::getline(ss, locationName, delimiter) &&
            std::getline(ss, locationId, delimiter) &&
            std::getline(ss, code, delimiter) &&
            std::getline(ss, parking, L'\r'))
        {
            // Convert the ID from string to integer
            try
            {
                locationId.erase(std::remove(locationId.begin(), locationId.end(), ','), locationId.end());
                id = std::stoi(locationId);
            }
            catch ([[maybe_unused]] const std::invalid_argument &e)
            {
                std::wcerr << L"Invalid ID format: " << line << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            try
            {
                parking.erase(std::remove(parking.begin(), parking.end(), ','), parking.end());
                parkingValue = std::stoi(parking);
            }
            catch ([[maybe_unused]] const std::invalid_argument &e)
            {
                std::wcerr << L"Invalid parking format in Locations: " << line << std::endl;
                continue; // Skip this line if max delivery is not a valid integer
            }
            cityGraph->addVertex(Location(locationName, id, code, parkingValue));
        }
    }

    file.close();
}

void CSVReader::readDistanceData(Graph<Location> *cityGraph)
{
    std::wifstream file(filename); // Use wide file stream
    if (!file.is_open())
    {
        std::wcerr << L"Error: Unable to open file " << filename << std::endl;
        return;
    }

    file.imbue(std::locale("pt_PT.UTF-8"));
    // Skip the header line
    std::wstring header;
    std::getline(file, header);

    // Read CSV data
    std::wstring line;
    while (std::getline(file, line))
    {
        std::wstringstream ss(line); // Use wide stringstream
        std::wstring Location1, Location2, drivingTime, walkingTime;
        int drivingTimeValue, walkingTimeValue;

        // Assuming the last column is not needed
        if (std::getline(ss, Location1, delimiter) &&
            std::getline(ss, Location2, delimiter) &&
            std::getline(ss, drivingTime, delimiter) &&
            std::getline(ss, walkingTime, L'\r'))
        {
            try
            {
                drivingTime.erase(std::remove(drivingTime.begin(), drivingTime.end(), ','), drivingTime.end());
                if (drivingTime == L"X")
                {
                    drivingTimeValue = -1;
                }
                else
                {
                    drivingTimeValue = std::stoi(drivingTime);
                }
            }
            catch ([[maybe_unused]] const std::invalid_argument &e)
            {
                std::wcerr << L"Invalid driving time in distances: " << line << std::endl;
                continue; // Skip this line if ID is not a valid integer
            }
            try
            {
                walkingTime.erase(std::remove(walkingTime.begin(), walkingTime.end(), ','), walkingTime.end());
                walkingTimeValue = std::stoi(walkingTime);
            }
            catch ([[maybe_unused]] const std::invalid_argument &e)
            {
                std::wcerr << L"Invalid walking time in distances: " << line << std::endl;
                continue; // Skip this line if demand is not a valid integer
            }
            Vertex<Location> *location1Vertex = nullptr;
            Vertex<Location> *location2Vertex = nullptr;
            for (Vertex<Location> *l1 : cityGraph->getVertexSet())
            {
                if (l1->getInfo().getCode() == Location1)
                {
                    location1Vertex = l1;
                    break;
                }
            }
            for (Vertex<Location> *l2 : cityGraph->getVertexSet())
            {
                if (l2->getInfo().getCode() == Location2)
                {
                    location2Vertex = l2;
                    break;
                }
            }
            if (location1Vertex && location2Vertex)
            {
                location1Vertex->addEdge(location2Vertex, walkingTimeValue, drivingTimeValue);
                location2Vertex->addEdge(location1Vertex, walkingTimeValue, drivingTimeValue);
            }
            else
            {
                std::wcerr << L"One or both the locations were not found in the system." << line << std::endl;
            }
        }
    }

    file.close();
}
