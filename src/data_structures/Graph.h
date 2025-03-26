/**
* @file Graph.h
 * @brief Contains the template definitions for the Graph, Vertex, and Edge classes.
 *
 * This header provides a flexible graph data structure supporting directed and bidirectional edges,
 * as well as weighted paths for multiple transportation modes (e.g., walking and driving).
 * It includes all core components needed for graph-based algorithms and routing logic.
 */

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "./MutablePriorityQueue.h" ///< Required for priority-based graph algorithms (e.g., Dijkstra).

/**
 * @brief Forward declaration of Edge class.
 *
 * Needed because Vertex and Edge reference each other.
 * @tparam T Type stored in the graph nodes.
 */
template <class T>
class Edge;

/**
 * @brief Represents positive infinity for weighted graph algorithms.
 */
#define INF std::numeric_limits<double>::max()


/************************* Vertex  **************************/

/**
 * @brief Represents a vertex (node) in a graph.
 *
 * Each vertex holds information of generic type `T` and maintains a list of outgoing and incoming edges.
 * It also includes various auxiliary fields for graph algorithms like DFS, BFS, Dijkstra, and Tarjan's SCC.
 *
 * @tparam T The data type stored in the vertex.
 */
template <class T>
class Vertex {
public:
    /**
     * @brief Constructs a vertex with the given information.
     * @param in The information to store in the vertex.
     */
    Vertex(T in);

    /**
     * @brief Comparison operator for priority queue operations.
     */
    bool operator<(Vertex<T> & vertex) const;

    /// @name Getters
    ///@{
    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    int getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;
    int getQueueIndex() const;
    int getLow() const;
    int getNum() const;
    ///@}

    /// @name Setters
    ///@{
    void setInfo(T info);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setLow(int value);
    void setNum(int value);
    void setQueueIndex(int value);
    void setIndegree(unsigned int indegree);
    void setDist(int dist);
    void setPath(Edge<T> *path);
    ///@}

    /**
     * @brief Adds a new edge from this vertex to another.
     *
     * @param d Destination vertex.
     * @param walking Weight or cost of walking.
     * @param driving Weight or cost of driving.
     * @return Pointer to the created edge.
     */
    Edge<T> * addEdge(Vertex *d, double walking, double driving);

    /**
     * @brief Removes the edge from this vertex to the vertex containing the given value.
     *
     * @param in The value identifying the destination vertex.
     * @return True if an edge was removed, false otherwise.
     */
    bool removeEdge(T in);

    /**
     * @brief Removes all outgoing edges from this vertex.
     */
    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;

protected:
    T info;                                ///< The data stored in the vertex.
    std::vector<Edge<T> *> adj;            ///< Outgoing edges.
    std::vector<Edge<T> *> incoming;       ///< Incoming edges.

    // Auxiliary fields used by graph algorithms
    bool visited = false;                  ///< Used in traversal algorithms.
    bool processing = false;               ///< Used for cycle detection (e.g. isDAG).
    int low = -1, num = -1;                ///< Used by Tarjan's algorithm for SCC.
    unsigned int indegree;                 ///< Used in topological sorting.
    int dist = 0;                          ///< Used in shortest path algorithms.
    Edge<T> *path = nullptr;               ///< Path pointer used in algorithms like Dijkstra.
    int queueIndex = 0;                    ///< Required by MutablePriorityQueue and Union-Find.

    /**
     * @brief Deletes a specific edge from the adjacency list.
     *
     * @param edge Pointer to the edge to delete.
     */
    void deleteEdge(Edge<T> *edge);
};

/********************** Edge  ****************************/

/**
 * @brief Represents an edge (connection) between two vertices in a graph.
 *
 * Each edge supports two weight types: one for walking and one for driving.
 * Edges can also be marked as available or unavailable and support bidirectional links.
 *
 * @tparam T The type of data stored in the vertices this edge connects.
 */
template <class T>
class Edge {
public:
    /**
     * @brief Constructs an edge between two vertices with given travel times.
     *
     * @param orig Pointer to the origin vertex.
     * @param dest Pointer to the destination vertex.
     * @param walking Time or cost associated with walking.
     * @param driving Time or cost associated with driving.
     */
    Edge(Vertex<T> *orig, Vertex<T> *dest, double walking, double driving);

    /// @name Getters
    ///@{
    Vertex<T> * getDest() const;
    Vertex<T> * getOrig() const;

    /**
     * @brief Gets the travel time based on travel mode.
     *
     * @param isWalking If true, returns walking time; otherwise, driving time.
     * @return Travel time.
     */
    double getTime(bool isWalking) const;

    /**
     * @brief Checks whether the edge is currently available.
     *
     * @return True if the edge is available, false otherwise.
     */
    bool isAvailable() const;

    /**
     * @brief Returns the reverse edge (used for bidirectional edges).
     *
     * @return Pointer to the reverse edge.
     */
    Edge<T> *getReverse() const;
    ///@}

    /// @name Setters
    ///@{
    /**
     * @brief Sets the availability status of the edge.
     *
     * @param isAvailable True to make the edge available, false otherwise.
     */
    void setAvailability(bool isAvailable);

    /**
     * @brief Sets the reverse edge for bidirectional connections.
     *
     * @param reverse Pointer to the reverse edge.
     */
    void setReverse(Edge<T> *reverse);
    ///@}

protected:
    Vertex<T> * dest;        ///< Destination vertex.
    double walkingTime;      ///< Time/cost for walking through this edge.
    double drivingTime;      ///< Time/cost for driving through this edge.
    bool available = true;   ///< Availability of this edge (e.g., blocked roads).

    Vertex<T> *orig;         ///< Origin vertex.
    Edge<T> *reverse = nullptr; ///< Reverse edge for bidirectional links.
};


/********************** Graph  ****************************/

/**
 * @brief Represents a generic graph structure using adjacency lists.
 *
 * Supports vertex and edge management, as well as support for bidirectional and weighted edges
 * (walking and driving). It also includes auxiliary fields for pathfinding algorithms such as Floyd-Warshall.
 *
 * @tparam T The type of data stored in each vertex.
 */
template <class T>
class Graph {
public:
    /**
     * @brief Destructor to clean up dynamic memory used by the graph.
     */
    ~Graph();

    /**
     * @brief Finds a vertex with the given content.
     *
     * @param in The content to search for.
     * @return Pointer to the vertex if found, nullptr otherwise.
     */
    Vertex<T> *findVertex(const T &in) const;

    /**
     * @brief Adds a vertex with the given content to the graph.
     *
     * @param in The content to store in the new vertex.
     * @return True if the vertex was added successfully, false if a duplicate exists.
     */
    bool addVertex(const T &in);

    /**
     * @brief Removes the vertex with the given content from the graph.
     *
     * @param in The content identifying the vertex to remove.
     * @return True if the vertex was found and removed, false otherwise.
     */
    bool removeVertex(const T &in);

    /**
     * @brief Adds a directed edge from one vertex to another.
     *
     * @param sourc The content of the source vertex.
     * @param dest The content of the destination vertex.
     * @param walking Walking weight of the edge.
     * @param driving Driving weight of the edge.
     * @return True if the edge was successfully added, false otherwise.
     */
    bool addEdge(const T &sourc, const T &dest, double walking, double driving);

    /**
     * @brief Removes the edge from one vertex to another.
     *
     * @param source The content of the source vertex.
     * @param dest The content of the destination vertex.
     * @return True if the edge was found and removed, false otherwise.
     */
    bool removeEdge(const T &source, const T &dest);

    /**
     * @brief Adds a bidirectional edge between two vertices.
     *
     * @param sourc The content of the first vertex.
     * @param dest The content of the second vertex.
     * @param walking Walking weight for both directions.
     * @param driving Driving weight for both directions.
     * @return True if both edges were added successfully, false otherwise.
     */
    bool addBidirectionalEdge(const T &sourc, const T &dest, double walking, double driving);

    /**
     * @brief Gets the total number of vertices in the graph.
     *
     * @return The number of vertices.
     */
    int getNumVertex() const;

    /**
     * @brief Gets the list of all vertices in the graph.
     *
     * @return Vector of pointers to vertices.
     */
    std::vector<Vertex<T> *> getVertexSet() const;

protected:
    std::vector<Vertex<T> *> vertexSet;    ///< Set of all vertices in the graph.

    double ** distMatrix = nullptr;        ///< Distance matrix used in Floyd-Warshall.
    int **pathMatrix = nullptr;            ///< Path matrix used in Floyd-Warshall.

    /**
     * @brief Finds the index of the vertex with the given content.
     *
     * @param in The content to search for.
     * @return Index of the vertex, or -1 if not found.
     */
    int findVertexIdx(const T &in) const;

    // Possibly used internally to set path pointers in algorithms like Prim or Kruskal.
    // No implementation was shown for this yet.
};

/**
 * @brief Deletes a dynamically allocated matrix of integers.
 *
 * @param m Pointer to the matrix.
 * @param n Number of rows.
 */
void deleteMatrix(int **m, int n);

/**
 * @brief Deletes a dynamically allocated matrix of doubles.
 *
 * @param m Pointer to the matrix.
 * @param n Number of rows.
 */
void deleteMatrix(double **m, int n);



/************************* Vertex  **************************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *d, double walking, double driving) {
    auto newEdge = new Edge<T>(this, d, walking, driving);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        Vertex<T> *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
template <class T>
void Vertex<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
int Vertex<T>::getLow() const {
    return this->low;
}

template <class T>
void Vertex<T>::setLow(int value) {
    this->low = value;
}

template <class T>
int Vertex<T>::getNum() const {
    return this->num;
}

template <class T>
void Vertex<T>::setNum(int value) {
    this->num = value;
}

template<class T>
void Vertex<T>::setQueueIndex(int value) {
    this->queueIndex = value;
}

template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

template <class T>
bool Vertex<T>::isProcessing() const {
    return this->processing;
}

template <class T>
unsigned int Vertex<T>::getIndegree() const {
    return this->indegree;
}

template <class T>
int Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template<class T>
int Vertex<T>::getQueueIndex() const {
    return this->queueIndex;
}

template <class T>
void Vertex<T>::setInfo(T in) {
    this->info = in;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

template <class T>
void Vertex<T>::setProcessing(bool processing) {
    this->processing = processing;
}

template <class T>
void Vertex<T>::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

template <class T>
void Vertex<T>::setDist(int dist) {
    this->dist = dist;
}

template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

template <class T>
void Vertex<T>::deleteEdge(Edge<T> *edge) {
    Vertex<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double walking, double driving): orig(orig), dest(dest), walkingTime(walking), drivingTime(driving) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

template <class T>
double Edge<T>::getTime(bool isWalking) const {
    return isWalking ? walkingTime : drivingTime;
}

template <class T>
bool Edge<T>::isAvailable() const {
    return available;
}

template <class T>
void Edge<T>::setAvailability(bool isAvailable) {
    available = isAvailable;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return this->reverse;
}

template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}

/********************** Graph  ****************************/

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double walking, double driving) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, walking, driving);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, double walking, double driving) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, walking, driving);
    auto e2 = v2->addEdge(v1, walking, driving);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

#endif /* DA_TP_CLASSES_GRAPH */