/*
 * Name: Qing Huang <qih008>
 * Project: PA2
 * Date: 7/12/2014
 */

#include "HCNode.hpp"

/*
 * Comapare this HCNode and other for priority ordering.
 * Smaller count means higher priority.
 * Use node symbol for deterministic tiebreaking.
 */
bool HCNode::operator<(const HCNode& other)
{
  if(count != other.count)  // check if count is equal
    return count > other.count; 
  else                     // if not equal, use symbol value
    return symbol < other.symbol;
};

