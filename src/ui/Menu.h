//
// Created by barroco on 3/12/25.
//

#ifndef MENU_H
#define MENU_H

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../env_friendly_routes/HybridRoutes.h"
#include "../route_planning/Dijkstra.h"
#include "../utils/Utils.h"

void menu(Graph<Location> *cityGraph);
void printMenuOptions();
int getUserChoice(int min, int max);

#endif //MENU_H
