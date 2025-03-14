#include "RestrictedRoutePlanning.h"

namespace RestrictedRoutePlanning {

void planRestrictedRoute(Graph<Location>* cityGraph) {
    Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;
    if (!chooseStartAndEndingCities(cityGraph, startPoint, endPoint)) {
        std::cerr << "Error: Didn't find one or both cities" << std::endl;
        return;
    }

    chooseNodesAndSegmentsToAvoid(cityGraph);
    std::vector<Vertex<Location>*> stopLocations = chooseMiddlePoint(cityGraph);

    double bestDistance = 0;
    std::vector<Vertex<Location>*> totalPath = findMultiStopRoute(cityGraph, startPoint, endPoint, stopLocations, bestDistance);

    if (!totalPath.empty()) {
        printRoute(totalPath, bestDistance);
    }
}

std::vector<Vertex<Location>*> findMultiStopRoute(Graph<Location>* cityGraph, Vertex<Location>* start, Vertex<Location>* end, std::vector<Vertex<Location>*>& stopLocations, double& bestDistance) {
    std::vector<Vertex<Location>*> totalPath;
    bool success = true;
    Vertex<Location>* currentStart = start;

    for (Vertex<Location>* stop : stopLocations) {
        std::vector<Vertex<Location>*> path = dijkstra(cityGraph, currentStart, stop);
        if (!path.empty()) {
            bestDistance += path.back()->getDist();
            totalPath.insert(totalPath.end(), path.begin(), path.end() - 1);
        } else {
            success = false;
            break;
        }
        currentStart = stop;
    }

    if (success) {
        std::vector<Vertex<Location>*> path = dijkstra(cityGraph, currentStart, end);
        if (!path.empty()) {
            bestDistance += path.back()->getDist();
            totalPath.insert(totalPath.end(), path.begin(), path.end());
            return totalPath;
        } else {
            std::cerr << "Error: Didn't find a path from " << currentStart->getInfo().getName() << " to " << end->getInfo().getName() << "." << std::endl;
        }
    } else {
        std::cerr << "Error: Couldn't complete the route through all stops." << std::endl;
    }

    return {};
}

void printRoute(const std::vector<Vertex<Location>*>& path, double bestDistance) {
    if (path.empty()) {
        std::cerr << "Error: No valid route found." << std::endl;
        return;
    }

    std::cout << "Best Route: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i]->getInfo().getName() << "(" << path[i]->getInfo().getId() << ")";
        if (i < path.size() - 1) {
            std::cout << " -> ";
        } else {
            std::cout << "\t Best Time: " << bestDistance << std::endl;
        }
    }
}

}


