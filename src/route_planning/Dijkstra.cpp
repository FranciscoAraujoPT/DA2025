#include "Dijkstra.h"


std::vector<Vertex<Location>*> dijkstra(const Graph<Location>* city, Vertex<Location>* src, Vertex<Location>* dest) {
    std::vector<Vertex<Location>*> path;
    if (!src || !dest) {
        std::cout << "Invalid source or destination!" << std::endl;
        return path;
    }

    if (src == dest) {
        std::cout << "Source and destination are the same!" << std::endl;
        path.push_back(src);
        return path;
    }

    MutablePriorityQueue<Vertex<Location>> pq;

    // **Initialize distances and paths**
    for (Vertex<Location>* location : city->getVertexSet()) {
        location->setVisited(false);
        location->setPath(nullptr);
        location->setDist(std::numeric_limits<double>::infinity());
        location->setQueueIndex(0);
    }

    src->setDist(0);
    pq.insert(src);

    while (!pq.empty()) {
        Vertex<Location>* current = pq.extractMin();
        current->setVisited(true);

        if (current == dest) break;  // Stop early if destination is reached

        for (Edge<Location>* street : current->getAdj()) {
            if (street->getTime(false) == -1 || !street->isAvailable()) {
                continue;
            }
            Vertex<Location>* next = street->getDest();

            if (next->isVisited() || !next->getInfo().isAvailable()) {
                continue;  // Skip visited nodes
            }

            double newDist = current->getDist() + street->getTime(false);

            if (newDist < next->getDist()) {
                next->setDist(newDist);
                next->setPath(street);  // Store the edge, not the vertex
                if (next->getQueueIndex() == 0) {  // If not in the queue, insert it
                    pq.insert(next);
                } else {  // If already in the queue, update it
                    pq.decreaseKey(next);
                }
            }
        }
    }

    // **If no path was found**
    if (dest->getDist() == std::numeric_limits<double>::infinity()) {
        return path;
    }

    // **Reconstruct path using edges**

    Vertex<Location>* v = dest;

    while (v != src) {
        Edge<Location>* edge = v->getPath();
        if (!edge) {
            std::cerr << "Error: Path reconstruction failed!" << std::endl;
            return path;
        }
        path.push_back(v);
        v = edge->getOrig();  // Move to previous vertex
    }
    path.push_back(src);
    std::reverse(path.begin(), path.end());

    return path;
}