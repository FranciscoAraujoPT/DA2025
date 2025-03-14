#include "IndependentRoutePlanning.h"

namespace IndependentRoutePlanning {

    void planDrivingRoute(Graph<Location>* cityGraph) {
        Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;
        if (!Utils::chooseStartAndEndingCities(cityGraph, startPoint, endPoint)) {
            std::cerr << "Error: Didn't find one or both cities" << std::endl;
            return;
        }

        std::vector<Vertex<Location>*> path = findBestDrivingRoute(cityGraph, startPoint, endPoint);
        if (!path.empty()) {
            std::cout << "Best Driving Route: ";
            Utils::printRoute(path, path.back()->getDist());

            // Find and print the alternative route
            path = findBestDrivingRoute(cityGraph, startPoint, endPoint);
            if (!path.empty()) {
                std::cout << "Best Alternative Driving Route: ";
                Utils::printRoute(path, path.back()->getDist());
            }
            else {
                std::cout << "No Alternative Driving Route Detected!" << std::endl;
            }
        } else {
            std::cout << "No Driving Route Detected!" << std::endl;
        }
    }

    std::vector<Vertex<Location>*> findBestDrivingRoute(Graph<Location>* cityGraph, Vertex<Location>* start, Vertex<Location>* end) {
        std::vector<Vertex<Location>*> path = dijkstra(cityGraph, start, end);

        // Mark intermediate nodes as unavailable
        for (Vertex<Location>* node : path) {
            if (node != start && node != end) {
                Location aux = node->getInfo();
                aux.setAvailability(false);
                node->setInfo(aux);
            }
        }

        return path;
    }

}
