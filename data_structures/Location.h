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
    Location(std::string name, int id, std::string code, bool parking);

    // Getters
    std::string getName() const;
    int getId() const;
    std::string getCode() const;
    bool hasParking() const;
    bool isAvailable() const;

    // Setters
    void setName(const std::string &newName);
    void setId(int newId);
    void setCode(const std::string &newCode);
    void setParking(bool hasParking);
    void setAvailability(bool isAvailable);

    // Overload comparison operators (needed for use in Graph)
    bool operator==(const Location &other) const;

    // Overload stream output for easy printing
    friend std::ostream &operator<<(std::ostream &os, const Location &loc);

private:
    std::string name;  // Location name
    int id;            // Unique identifier
    std::string code;  // Location code
    bool parking;      // Availability of parking (true/false)
    bool available = true;
};

#endif //LOCATION_H
