#ifndef HYBRID_ROUTES_H
#define HYBRID_ROUTES_H

#include <vector>
#include <unordered_map>
#include <string>

#include "../data_structures/Graph.h"
#include "../data_structures/Location.h"
#include "../algorithm/Dijkstra.h"
#include "../utils/Utils.h"

namespace HybridRoutes {
    void handleEnvFriendlyRoute(Graph<Location>* cityGraph);
}

#endif
