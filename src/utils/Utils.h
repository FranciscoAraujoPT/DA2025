//
// Created by barroco on 3/12/25.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"

int getValidatedInt(const std::string& prompt);
int chooseStartAndEndingCities(Graph<Location>* cityGraph, Vertex<Location> *&startPoint, Vertex<Location> *&endPoint);
int chooseNodesAndSegmentsToAvoid(Graph<Location>* cityGraph);
std::vector<Vertex<Location>*> chooseMiddlePoint(Graph<Location>* cityGraph);
int chooseStartAndEndingCitiesEnvFriendly(Graph<Location>* cityGraph, Vertex<Location> *&startPoint, Vertex<Location> *&endPoint, int &maxWalkingTime);
int checkStartAndEndingCitiesAdjacency(std::vector<Edge<Location> *> streets, int destCity);
void printReport(const std::string& reportType, const Graph<Location>* cityGraph);

#endif //UTILS_H
