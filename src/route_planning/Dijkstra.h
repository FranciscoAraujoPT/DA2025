//
// Created by barroco on 3/12/25.
//

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"

std::vector<Vertex<Location>*> dijkstra(const Graph<Location>* city, Vertex<Location>* src, Vertex<Location>* dest);

#endif //DIJKSTRA_H
