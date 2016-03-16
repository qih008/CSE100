/*
 * Name: Qing Huang <qih008>
 * Project: PA3
 * Date: 7/21/2014
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <unordered_map>
#include <string.h>
#include <iostream>

#include "Edge.hpp"

using namespace std;
/*
 * Represents a Vertex in a graph.
 *
 * Vertices are connected to other Vertices via Edges. Each Vertex
 * maintains a collection of all Edges that originate from it.
 */
class Vertex {
    // Graph needs access to Edge map for Dijkstra/Prim's algorithms.
    friend class UndirectedGraph;
    
  public:
    /**
     * Initialize the Vertex with the given name.
     */
    Vertex(const std::string &name);

    /**
     * Add an edge to this Vertex.
     */
    bool addEdge(Vertex *to, unsigned int cost, unsigned int length);
    
    /**
     * Determines if this Vertex has an edge to the given Vertex.
     *
     * Returns true if it does, and false if it doens't.
     */
    bool hasEdge(Vertex *to) const;
    
    /**
     * Returns the Edge to the given Vertex.
     *
     * If the Edge does not exist, returns a nullptr.
     */
    Edge getEdge(Vertex *to) const;

    /**
     * Removes an edge from this Vertex.
     *
     * Returns true if an edge existed previously, and false if not.
     */
    bool removeEdge(Vertex *to);
    
    /**
     * Returns the Vertex's name.
     */
    const std::string &getName() const;
    
    /**
     * Gets the Vertex's distance value.
     */
    unsigned int getDistance() const;

    /**
     * Sets the Vertex's distance value.
     */
    void setDistance(unsigned int distance);
    
    /**
     * Gets the Vertex's visited state.
     */
    bool wasVisited() const;

    /**
     * Sets the Vertex's visited state.
     */
    void setVisited(bool visited);

    /**
     * Clears all edges from this Vertex.
     */
    void clearEdges();

    /**
     * Gets total cost of all edges terminating at this Vertex.
     */
    unsigned int totalEdgeCost() const;

    /**
     * Comparison functor for use with priority queues. Lesser-distance
     * Vertices sort before greater-distance Vertices.
     *
     * Same-distance vertices sort by their names. This guarantees 
     * unambiguous ordering of all posible Vertices in the queue.
     */
    class DistanceComparator {
      public:
        bool operator()(const Vertex *left,
                const Vertex *right);
    };
    
  private:
    /**
     * Returns a reference to the internal map of Edges.
     */
    const std::unordered_map<std::string, Edge> &getEdges() const;

    /**
     * Name of this Vertex.
     */
    std::string name;
    
    /**
     * Distance of this Vertex from initial Vertex.
     * Used by Dijkstra's algorithm.
     */
    unsigned int distance;
    
    /**
     * Whether this node has been visited.
     * Used by Prim's algorithm.
     */
    bool visited;

    /**
     * Map of adjacent Vertex name to Edge describing the adjacency.
     */
    std::unordered_map<std::string, Edge> edges;
};

#endif
