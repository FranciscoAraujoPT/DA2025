#ifndef RESTRICTED_ROUTE_PLANNING_H
#define RESTRICTED_ROUTE_PLANNING_H

#include <vector>
#include <iostream>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../algorithm/Dijkstra.h"
#include "../utils/Utils.h"

namespace RestrictedRoutePlanning {
    void planRestrictedRoute(Graph<Location>* cityGraph);
    std::vector<Vertex<Location>*> findMultiStopRoute(Graph<Location>* cityGraph, Vertex<Location>* start, Vertex<Location>* end, std::vector<Vertex<Location>*>& stopLocations, double& bestDistance);
}

#endif
