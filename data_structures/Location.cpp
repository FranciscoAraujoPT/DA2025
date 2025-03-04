//
// Created by macbook on 21/02/2025.
//

#include "../data_structures/Location.h"


// Constructor implementation
Location::Location(std::wstring name, int id, std::wstring code, bool parking)
    : name(std::move(name)), id(id), code(std::move(code)), parking(parking) {}

// Getters
std::wstring Location::getName() const { return name; }
int Location::getId() const { return id; }
std::wstring Location::getCode() const { return code; }
bool Location::hasParking() const { return parking; }
bool Location::isAvailable() const { return available; }

// Setters
void Location::setName(const std::wstring &newName) { name = newName; }
void Location::setId(int newId) { id = newId; }
void Location::setCode(const std::wstring &newCode) { code = newCode; }
void Location::setParking(bool hasParking) { parking = hasParking; }
void Location::setAvailability(bool isAvailable) { available = isAvailable; }

// Overload comparison operator
bool Location::operator==(const Location &other) const { return id == other.id; }

// Overload stream output operator for wide characters
std::wostream &operator<<(std::wostream &os, const Location &loc) {
    os << L"Location: " << loc.getName().c_str() << L" (ID: " << loc.getId() << L", Code: "
       << loc.getCode().c_str() << L", Parking: " << (loc.hasParking()? L"Yes" : L"No") << L")";
    return os;
}


