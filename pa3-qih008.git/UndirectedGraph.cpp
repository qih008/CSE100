/*
 * Name: Qing Huang <qih008>
 * Project: PA3
 * Date: 7/23/2014
 */

#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

#include <limits>

using namespace std;
// Method implementations here

pair<unordered_map<string, Vertex*>::iterator, bool> result1;
unordered_map<string, Vertex*>::const_iterator start;
unordered_map<string, Vertex*>::const_iterator dest;
unordered_map<string, Vertex*>::const_iterator itemp;
Vertex *v;

UndirectedGraph::UndirectedGraph()
{                      // Constructs an empty UndirectedGraph
  this->vertices.clear();
  v = nullptr;
}

UndirectedGraph::~UndirectedGraph()
{                      // Destructs an UndirectedGraph
  vertices.clear();
  v = nullptr;
}

bool UndirectedGraph::hasVertex(const std::string &name) const
{                      // Determines if the graph contains the named vertex
  dest = vertices.find(name);
  if(dest != vertices.end()) // check if map has the vertex's name
    return true;
  else return false;
}

bool UndirectedGraph::addVertex(const std::string &name)
{                      // Insert a vertex into the graph
  v = new Vertex(name); // create the new vertex with given name
  result1 = vertices.insert(make_pair(name, v)); // insert to map
  return result1.second;
}

bool UndirectedGraph::hasEdge(const std::string &from, 
                              const std::string &to) const
{                       // Determines if the graph contains the named edge
  if(hasVertex(from) && hasVertex(to)) // if both vertices exist
  {
    start = vertices.find(from);
    dest = vertices.find(to);
    return start->second->hasEdge(dest->second); // check named edge
  }
  else return false;
}

bool UndirectedGraph::addEdge(const std::string &from, const std::string &to,
                              unsigned int cost, unsigned int length)
{                           // inserts an edge into the graph
  if(!hasEdge(from, to))    // check if edge exist between two vertices
  {                       
    start = vertices.find(from);
    dest = vertices.find(to);
    start->second->addEdge(dest->second, cost, length);
    dest->second->addEdge(start->second, cost, length);
    return true;
  }
  else return false;        // if edge exist, update it, return false  
}

unsigned int UndirectedGraph::totalEdgeCost() const
{                       // returns the total cost of all edges in the graph
  unsigned int total = 0;
  for(dest = vertices.begin(); dest != vertices.end(); ++dest)
  {
    total = total + dest->second->totalEdgeCost();
  }
  return total;
}

unsigned int UndirectedGraph::totalDistance(const std::string &from)
{ // return the distance from given vertex to all other vertices in the graph
  
  int infinity = numeric_limits<int>::max();   // set infinity
  priority_queue<Vertex*, vector<Vertex*>, Vertex::DistanceComparator> pq;
  
  for(dest = vertices.begin(); dest != vertices.end(); ++dest)
  {                                       // loop through all vertices
    dest->second->setDistance(infinity);  // set all vertices dist to infi
    dest->second->setVisited(false);      // set all vertices vistied to false
  }

  dest = vertices.find(from);            // set iter to current vertex
  dest->second->setDistance(0);          // set cur dist to 0
  pq.push(dest->second);                 // enqueue

  unordered_map<string, Edge>::iterator iter;
  while(pq.size() != 0)
  {
    v = pq.top();
    pq.pop();                             // dequeue the head of queue
    
    if(!v->wasVisited())                  // if v's visit if true, continue
    {  
      v->setVisited(true);                // else set v's visit to true
      for(iter = v->edges.begin(); iter != v->edges.end(); ++iter)
      {                                     // v is edge's from pointer
        Vertex *ver;
        ver = iter->second.getTo();         // get the edge's to pointer
        if(!ver->wasVisited())
        {            // check those adjacent nodes whose done flag is not true
          unsigned int dist = iter->second.getLength() + v->getDistance();
	  if(dist < ver->getDistance())     // compare path length with distance
	    ver->setDistance(dist);         // if less than, repalce distance
	  pq.push(ver);                     // push it to queue
        }
      }
    }
  }
  unsigned int distance = 0;
  for(dest = vertices.begin(); dest != vertices.end(); ++dest)
  {                         // loop through all vertices, add their dist togather
    distance = distance + dest->second->getDistance();
  }
  return distance;
}

unsigned int UndirectedGraph::totalDistance()
{ // returns the distance from all vertices to all other vertices in the graph
  unsigned int distance = 0;
  for(start = vertices.begin(); start != vertices.end(); ++start)
  {
    distance = distance + totalDistance(start->second->getName());
  }
  return distance;
}

UndirectedGraph UndirectedGraph::minSpanningTree()
{                                        // return type UndirectedGraph
  priority_queue<Edge, vector<Edge>, EdgeComp> mpq;
  int infinity = numeric_limits<int>::max();   // set infinity
  UndirectedGraph *temp = new UndirectedGraph();
  unsigned int test = infinity;

  for(itemp = vertices.begin(); itemp != vertices.end(); ++itemp)
  {                     // EC:try to start with every vertex to find min length
    UndirectedGraph *mst = new UndirectedGraph();  // create a new graph
    for(dest = vertices.begin(); dest != vertices.end(); ++dest)
      dest->second->setVisited(false);     // set all vertices vistied to false
    v = itemp->second;                     // use cur vertex to start
    v->setVisited(true);
 
    Vertex* ver;
    unordered_map<string, Edge>::iterator miter;
    for(miter = v->edges.begin(); miter != v->edges.end(); ++miter)
    {                             // get the start vertex's all adj edges
      ver = miter->second.getTo();         // get edge's dest pointer 
      if(!ver->wasVisited())               // if not visited
        mpq.push(miter->second);           // push edge
    }
    mst->addVertex(v->getName());          // add from vertex to new graph
    while(mpq.size() != 0)
    {
      Edge e = mpq.top();                  // current edge
      mpq.pop();
      ver = e.getTo();                     // get To pointer of cur edge
      if(!ver->wasVisited())               // check if visit To pointer
      {
        ver->setVisited(true);
        mst->addVertex(ver->getName());     // add vertex in new graph
        mst->addEdge(e.getFrom()->getName(), ver->getName(),
                     e.getCost(), e.getLength()); // add edge to new graph
        for(miter = ver->edges.begin(); miter != ver->edges.end(); miter++)
        {
          if(!miter->second.getTo()->wasVisited())
	    mpq.push(miter->second);       // push edge
        }
      }
    }
    if(mst->totalDistance() < test)  // comp cur graph with prev graph
    {                                // find the min length
      test = mst->totalDistance();
      temp = mst;
    }
  }
  return *temp;                      // return mst with min length
}

