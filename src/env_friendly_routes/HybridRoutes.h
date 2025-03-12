//
// Created by barroco on 3/12/25.
//

#ifndef HYBRID_ROUTES_H
#define HYBRID_ROUTES_H

#include <vector>
#include <unordered_map>
#include <string>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"

class HybridRoutes {
public:
    explicit HybridRoutes(Graph<Location>* cityGraph);
    void findBestHybridRoute(Graph<Location>* cityGraph, Vertex<Location>* src, Vertex<Location>* dest, int maxWalkingTime);
private:
    Graph<Location>* graph;

    std::unordered_map<Vertex<Location>*, double> computeDrivingDistances(const Graph<Location>* city, Vertex<Location>* src, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& drivingParentMap);
    std::unordered_map<Vertex<Location>*, double> computeWalkingDistances(const Graph<Location>* city, Vertex<Location>* dest, int maxWalkingTime, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>> &walkingParentMap);
    Vertex<Location>* findBestParkingSpot(std::unordered_map<Vertex<Location>*, double> &drivingDistances, std::unordered_map<Vertex<Location>*, double> &walkingDistances, int maxWalkingTime);
    std::vector<Vertex<Location>*> reconstructPath(Vertex<Location>* start, Vertex<Location>* end, std::unordered_map<Vertex<Location>*, std::vector<Vertex<Location>*>>& parentMap);
    void printPath(const std::vector<Vertex<Location>*>& path, const std::string& label);
};

#endif //HYBRID_ROUTES_H
