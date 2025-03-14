#include "IndependentRoutePlanning.h"

namespace IndependentRoutePlanning {

    void planDrivingRoute(Graph<Location>* cityGraph) {
        Vertex<Location> *startPoint = nullptr, *endPoint = nullptr;
        if (!chooseStartAndEndingCities(cityGraph, startPoint, endPoint)) {
            std::cerr << "Error: Didn't find one or both cities" << std::endl;
            return;
        }

        std::vector<Vertex<Location>*> path = findBestDrivingRoute(cityGraph, startPoint, endPoint);
        printRoute(path, "Best Driving Route: ");

        // Find and print the alternative route
        path = findBestDrivingRoute(cityGraph, startPoint, endPoint);
        if (!path.empty()) {
            printRoute(path, "Best Alternative Driving Route: ");
        }
        else {
            std::cout << "No Alternative Driving Route Detected!" << std::endl;
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

    void printRoute(const std::vector<Vertex<Location>*>& path, const std::string& label) {
        if (path.empty()) {
            std::cerr << "Error: No route found." << std::endl;
            return;
        }

        std::cout << label;
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->getInfo().getName();
            std::cout << "(" << path[i]->getInfo().getId() << ")";
            if (i < path.size() - 1) {
                std::cout << " -> ";
            } else {
                std::cout << "\t Best Time: " << path.back()->getDist() << std::endl;
            }
        }
    }

}
