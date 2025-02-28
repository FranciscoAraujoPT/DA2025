//
// Created by macbook on 24/02/2025.
//

#ifndef STREET_H
#define STREET_H

#include "Graph.h"
class Location;

class Street {
public:
    // Constructor
    Street(Edge<Location> s, double walkTime, double driveTime);

    // Get time based on transport mode
    double getTime(bool isWalking) const;
    Edge<Location>* getStreet();
    bool isAvailable() const;

    void setAvailability(bool isAvailable);
private:
    Edge<Location> street;  // Pointer to the original Edge<Location>
    double walkingTime;
    double drivingTime;
    bool available = true;
};



#endif //STREET_H
