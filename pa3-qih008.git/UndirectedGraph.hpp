/*
 * Name: Qing Huang <qih008>
 * Project: PA3
 * Date: 7/23/2014
 */

#ifndef UNDIRECTEDGRAPH_HPP
#define UNDIRECTEDGRAPH_HPP

#include <string>
#include <unordered_map>
#include <string.h>
#include <queue>

#include "Vertex.hpp"
#include "Edge.hpp"

/**
 * Implements an undirected graph. Any edge in the graph
 * represents a bidirectional connection between two vertices.
 * 
 * Implements methods for producing a minimum spanning tree of the
 * graph, as well as calculating the total length of the shortest
 * paths between each pair of vertices.
*/
class UndirectedGraph {
  public:
    /**
     * Constructs an empty UndirectedGraph with no vertices and
     * no edges.
     */
    UndirectedGraph();

    /**
     * Destructs an UndirectedGraph.
     */
    ~UndirectedGraph();
    
    /**
     * Determines if the graph contains the named vertex.
     *
     * Returns true if the edge exists, and false if not.
     */
    bool hasVertex(const std::string &name) const;
    
    /**
     * Inserts a vertex into the graph.
     *
     * Returns true if the vertex did not previously exist, and false if it
     * did.
     */
    bool addVertex(const std::string &name);

    /**
     * Determines if the graph contains the named edge.
     *
     * Returns true if the edge exists, and false if not.
     * If either Vertex does not exist, returns false.
     */
    bool hasEdge(const std::string &from, const std::string &to) const;

    /**
     * Inserts an edge into the graph. If an edge already exists between
     * the vertices, updates the cost and length of the edge to match the
     * passed parameters.
     *
     * If either of the named vertices does not exist, it is created.
     *
     * Returns true if the edge did not previously exist, and false if it did.
     */
    bool addEdge(const std::string &from, const std::string &to,
            unsigned int cost, unsigned int length);

    /**
     * Returns the total cost of all edges in the graph.
     *
     * Since this graph is undirected, is calcualted as the cost
     * of all Edges terminating at all Vertices, divided by 2.
     */
    unsigned int totalEdgeCost() const;
    
    /**
     * Removes all edges from the graph except those necessary to
     * form a minimum cost spanning tree of all vertices using Prim's
     * algorithm.
     *
     * The graph must be in a state where such a spanning tree
     * is possible. To call this method when a spanning tree is
     * impossible is undefined behavior.
     */
    //void minSpanningTree();
    UndirectedGraph minSpanningTree();
    //UndirectedGraph *minSpanningTree();
    /**
     * Determines the combined distance from the given Vertex to all
     * other Vertices in the graph using Dijkstra's algorithm.
     *
     * Returns max possible distance if the given Vertex does not appear
     * in the graph, or if any of the Vertices in the graph are not
     * reachable from the given Vertex. Otherwise, returns the combined
     * distance.
     */
    unsigned int totalDistance(const std::string &from);
    
    /**
     * Determines the combined distance from all Vertices to all other
     * Vertices in the graph.
     *
     * Returns max possible distance if the graph is not connected.
     */
    unsigned int totalDistance();
    
  private:
    /**
     * Map of vertex name to Vertex.
     */
    std::unordered_map<std::string, Vertex*> vertices;
};

/**
 * A 'function class' for use as the Compare class in a
 * priority_queue<Edge>.
 * For this to work, operator< must be defind to do
 * the right thing on Edge.
 */

class EdgeComp 
{
  public:
    bool operator()(Edge& e1, Edge& e2) const
    {
      return e1 < e2;
    }
};
      
#endif
