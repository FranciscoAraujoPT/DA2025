#ifndef MENU_H
#define MENU_H

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../route_planning/HybridRoutes.h"
#include "../route_planning/IndependentRoutePlanning.h"
#include "../route_planning/RestrictedRoutePlanning.h"
#include "../utils/Utils.h"

void menu(Graph<Location> *cityGraph);
void printMenuOptions();
int getUserChoice(int min, int max);

#endif
