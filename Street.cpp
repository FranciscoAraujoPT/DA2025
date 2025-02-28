//
// Created by macbook on 24/02/2025.
//

#include "Street.h"

// Constructor
Street::Street(Edge<Location> s, double walkTime, double driveTime)
    : street(s), walkingTime(walkTime), drivingTime(driveTime) {}

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
