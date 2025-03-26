/**
* @file Dijkstra.h
 * @brief Declares the Dijkstra algorithm function for shortest path computation.
 *
 * This function computes the shortest path between two vertices using Dijkstra's algorithm,
 * with support for early termination and walking-specific constraints.
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"

/**
 * @brief Computes the shortest path between two vertices using Dijkstra's algorithm.
 *
 * This function returns the shortest path from a source vertex to a destination vertex
 * in the given city graph. The graph is assumed to represent a weighted, directed graph
 * with non-negative edge weights.
 *
 * @param city Pointer to the graph representing the city.
 * @param src The starting vertex.
 * @param dest The destination vertex.
 * @param currentBest Optional upper bound on path cost; paths with a cost exceeding this value are skipped, enabling early exit and optimization.
 * @param isWalking Indicates whether walking time should be prioritized (true) or driving (false).
 * @return A vector of vertices representing the shortest path from src to dest.
 */
std::vector<Vertex<Location>*> dijkstra(const Graph<Location>* city, Vertex<Location>* src, Vertex<Location>* dest, int currentBest = std::numeric_limits<int>::max(), bool isWalking = false);

#endif // DIJKSTRA_H
