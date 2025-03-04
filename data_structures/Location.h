//
// Created by macbook on 21/02/2025.
//

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include <utility>

class Location {
public:
    // Constructor
    Location(std::wstring name, int id, std::wstring code, bool parking);

    // Getters
    std::wstring getName() const;
    int getId() const;
    std::wstring getCode() const;
    bool hasParking() const;
    bool isAvailable() const;

    // Setters
    void setName(const std::wstring &newName);
    void setId(int newId);
    void setCode(const std::wstring &newCode);
    void setParking(bool hasParking);
    void setAvailability(bool isAvailable);

    // Overload comparison operators (needed for use in Graph)
    bool operator==(const Location &other) const;

    // Overload stream output for easy printing
    friend std::ostream &operator<<(std::ostream &os, const Location &loc);

private:
    std::wstring name;  // Location name
    int id;            // Unique identifier
    std::wstring code;  // Location code
    bool parking;      // Availability of parking (true/false)
    bool available = true;
};

#endif //LOCATION_H
