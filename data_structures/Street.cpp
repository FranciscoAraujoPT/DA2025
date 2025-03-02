//
// Created by macbook on 24/02/2025.
//

#include "../data_structures/Street.h"

// Constructor
Street::Street(Edge<Location> s, double driveTime, double walkTime)
    : street(s), drivingTime(driveTime), walkingTime(walkTime) {}

// Get time based on transport mode
double Street::getTime(bool isWalking) const {
    return isWalking ? walkingTime : drivingTime;
}

Edge<Location>* Street::getStreet() {
    return &street;
}

bool Street::isAvailable() const {
    return available;
}

void Street::setAvailability(bool isAvailable) {
    available = isAvailable;
}
