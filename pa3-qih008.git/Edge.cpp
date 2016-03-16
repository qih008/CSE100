/*
 * Name: Qing Huang <qih008>
 * Project: PA3
 * Date: 7/21/2014
 */

#include "Edge.hpp"

// Method implementations here

Edge::Edge(Vertex *from, Vertex* to, unsigned int cost, unsigned int length):
           from(from), to(to), cost(cost), length(length){}

Vertex* Edge::getFrom() const
{
  return from;  // return pointer to this edge's originates
}

Vertex* Edge::getTo() const
{
  return to;    // return pointer to this edge's terminates
}

void Edge::setCost(unsigned int cost)
{
  this->cost = cost;  // set this edge's cost to input value
}

unsigned int Edge::getCost() const
{
  return cost;        // return this edge's cost
}

void Edge::setLength(unsigned int length)
{
  this->length = length;  // set this edge's length to input value
}

unsigned int Edge::getLength() const
{
  return length;          // return this edge's length
}

bool Edge::operator<(const Edge &right) const
{                            // smaller cost means higher priority
  if(cost != right.cost)
  {  
    return cost > right.cost;  // return true if this edge's cost is more
  }                            // than right's cost
  else return length > right.length;
}

