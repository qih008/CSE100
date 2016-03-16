/*
 * Name: Qing Huang <qih008>
 * Project: PA3
 * Date: 7/21/2014
 */

#include "Vertex.hpp"
#include "Edge.hpp"

// Method implementations here

pair<unordered_map<string, Edge>::iterator, bool> result;
unordered_map<string, Edge>::const_iterator it;

Vertex::Vertex(const std::string &name):name(name){}

bool Vertex::addEdge(Vertex *to, unsigned int cost, unsigned int length)
{
  result = edges.insert(make_pair(to->getName(), Edge(this, to, cost, length)));
  return result.second;
}

bool Vertex::hasEdge(Vertex *to) const
{                              // check if this Vertex has edge to the given Vertex
  it = edges.find(to->getName());
  if(it != edges.end())  // check if map has the same name
    return true;
  else return false;
}

Edge Vertex::getEdge(Vertex *to) const
{                              // returns the Edge to the given Vertex
  it = edges.find(to->getName());
  return it->second;           // return type Edge
}

bool Vertex::removeEdge(Vertex *to)
{                              // remove an edge from this Vertex
  if(hasEdge(to))              // if this Vertex has an edge
  {
    edges.erase(to->getName());  // erase it from the map
    return true;
  }
  else return false;
}

const string & Vertex::getName() const
{
  return this->name;                  // return Vertex's name
}

unsigned int Vertex::getDistance() const
{
  return distance;            // return vertex's distance value
}

void Vertex::setDistance(unsigned int distance)
{
  this->distance = distance;  // sets vertex's distance value
}

bool Vertex::wasVisited() const
{
  return visited;             // return visited state
}

void Vertex::setVisited(bool visited)
{
  this->visited = visited;    // sets vertex's visited state
}

void Vertex::clearEdges()
{
  edges.clear();              // clear all edges in the map
}

unsigned int Vertex::totalEdgeCost() const
{
  unsigned int total = 0;
  for(it = edges.begin(); it != edges.end(); ++it)
  {                           // loop throught the unordered_map
    total = total + it->second.getCost(); // add all edge's cost
  }
  return total;
}

bool Vertex::DistanceComparator::operator()(const Vertex *left, 
                                            const Vertex *right)
{
  if(left->distance != right->distance)  // check if distance equal
    return left->distance > right->distance;
  else 
    return left->name < right->name;
};

const std::unordered_map<std::string, Edge>& Vertex::getEdges() const
{
  return this->edges;
}
