#ifndef INDEPENDENT_ROUTE_PLANNING_H
#define INDEPENDENT_ROUTE_PLANNING_H

#include <vector>
#include <iostream>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../route_planning/Dijkstra.h"
#include "../utils/Utils.h"

namespace IndependentRoutePlanning {
    void planDrivingRoute(Graph<Location>* cityGraph);
    std::vector<Vertex<Location>*> findBestDrivingRoute(Graph<Location>* cityGraph, Vertex<Location>* start, Vertex<Location>* end);
    void printRoute(const std::vector<Vertex<Location>*>& path, const std::string& label);
}

#endif

