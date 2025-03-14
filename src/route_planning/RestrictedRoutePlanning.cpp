#include "RestrictedRoutePlanning.h"

namespace RestrictedRoutePlanning {

void planRestrictedRoute(Graph<Location>* cityGraph) {
    Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;
    if (!Utils::chooseStartAndEndingCities(cityGraph, startPoint, endPoint)) {
        std::cerr << "Error: Didn't find one or both cities" << std::endl;
        return;
    }

    Utils::chooseNodesAndSegmentsToAvoid(cityGraph);
    std::vector<Vertex<Location>*> stopLocations = Utils::chooseMiddlePoint(cityGraph);

    double bestDistance = 0;
    std::vector<Vertex<Location>*> totalPath = findMultiStopRoute(cityGraph, startPoint, endPoint, stopLocations, bestDistance);

    if (!totalPath.empty()) {
        std::cout << "Best Driving Route: ";
        Utils::printRoute(totalPath, bestDistance);
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

}


