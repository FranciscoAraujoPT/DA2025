/**
 * @file Location.h
 * @brief Defines the Location class representing a place in the city.
 *
 * The Location class stores details about locations, including their name, ID, code,
 * and whether they have parking facilities.
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <iostream>
#include <utility>

/**
 * @class Location
 * @brief Represents a location in the city with an identifier, name, and attributes.
 */
class Location {
public:
    /**
     * @brief Constructs a Location object.
     *
     * @param name The name of the location.
     * @param id A unique identifier for the location.
     * @param code A short code representing the location.
     * @param parking Indicates whether the location has parking facilities.
     */
    Location(std::string name, int id, std::string code, bool parking);

    /**
     * @brief Gets the name of the location.
     * @return The name of the location as a string.
     */
    std::string getName() const;

    /**
     * @brief Gets the unique ID of the location.
     * @return The location's unique ID.
     */
    int getId() const;

    /**
     * @brief Gets the location code.
     * @return The short code of the location.
     */
    std::string getCode() const;

    /**
     * @brief Checks if the location has parking facilities.
     * @return True if parking is available, false otherwise.
     */
    bool hasParking() const;

    /**
     * @brief Checks if the location is available.
     * @return True if available, false otherwise.
     */
    bool isAvailable() const;

    /**
     * @brief Sets the name of the location.
     * @param newName The new name to set.
     */
    void setName(const std::string& newName);

    /**
     * @brief Sets the location's unique ID.
     * @param newId The new ID to set.
     */
    void setId(int newId);

    /**
     * @brief Sets the location code.
     * @param newCode The new code to set.
     */
    void setCode(const std::string& newCode);

    /**
     * @brief Sets whether the location has parking.
     * @param hasParking True if the location has parking, false otherwise.
     */
    void setParking(bool hasParking);

    /**
     * @brief Sets the availability status of the location.
     * @param isAvailable True if available, false otherwise.
     */
    void setAvailability(bool isAvailable);

    /**
     * @brief Overloads the equality operator to compare locations.
     * @param other The location to compare against.
     * @return True if the locations are equal, false otherwise.
     */
    bool operator==(const Location& other) const;

    /**
     * @brief Overloads the stream insertion operator for printing.
     * @param os The output stream.
     * @param loc The location to print.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Location& loc);

private:
    std::string name;  /**< The name of the location. */
    int id;            /**< The unique identifier of the location. */
    std::string code;  /**< The short code representing the location. */
    bool parking;      /**< Indicates whether parking is available. */
    bool available = true; /**< Availability status of the location. */
};

#endif // LOCATION_H
