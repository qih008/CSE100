/*
 * Name: Qing Huang
 * Project: PA3
 * Date: 7/23/2014
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "UndirectedGraph.hpp"

using namespace std;

/**
 * Entry point into the netplan program.
 *
 * -Reads a file from the filesystem according to the specification for
 *  PA3, creating an UndirectedGraph.
 * -Finds the total cost & ping time of the graph as presented in the input
 *  file.
 * -Determines the minimum cost graph from the original graph.
 * -Finds the total cost & ping time of the minimum cost graph.
 * -Finds the change of cost & ping time from the original graph to the
 *  minimum cost graph.
 * -Prints the results to stdout.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main(int argc, char **argv) 
{
  if (argc != 2) 
  {
    std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
      return EXIT_FAILURE;
  }  
  std::ifstream in(argv[1]);
  if (!in) 
  {
    std::cerr << "Unable to open file for reading." << std::endl;
    return EXIT_FAILURE;
  }  
  // Implementation here
  UndirectedGraph g;
  string v1;
  string v2;
  double cost;
  double length;
  while(in.good())
  {
    in >> v1 >> v2 >> cost >> length;
    if(!in.good()) break;
    g.addVertex(v1);
    g.addVertex(v2);
    g.addEdge(v1, v2, cost, length);
  }
  unsigned int total = g.totalEdgeCost()/2;
  unsigned int distance = g.totalDistance();
  cout << total << endl;  

  UndirectedGraph mst = g.minSpanningTree();
  unsigned int msttotal = mst.totalEdgeCost()/2;
  cout << msttotal << endl;
  cout << total - msttotal << endl;

  cout << distance << endl;

  unsigned int mstdistance = mst.totalDistance();
  cout << mstdistance << endl;
  cout << mstdistance - distance << endl;

  return EXIT_SUCCESS;
}
