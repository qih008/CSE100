/*
 * Name: Qing Huang <qih008>
 * Project: PA2
 * Date: 7/12/2014
 */

#include "HCTree.hpp"

void clearNode(HCNode* node)
{
  if(node != nullptr) // only remove when node not null
  {
    if(node->c0 != nullptr) // traverse down to delete
      clearNode(node->c0);  // every node
    if(node->c1 != nullptr)
      clearNode(node->c1);
    delete node;
  }
}

HCTree::~HCTree()
{
  clearNode(root); // destructor
}

void HCTree::build(const vector<int>& freqs)
{
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

  for(int i=0; i<freqs.size(); i++)
  {
    leaves[i] = new HCNode(freqs[i],i); //create new nodes for leaves
    if(freqs[i] != 0)           // freqs not 0
      pq.push(leaves[i]);       // insert nodes to HC tree
  }

  if(pq.size() != 0)            // check empty case
  {
    while(pq.size() > 1)      // at least 2 nodes to merge
    {
      HCNode* h1 = pq.top();  // find higher priority node(smallest count)
      pq.pop();               // delete this node in queue
      HCNode* h2 = pq.top();  // find the second high to merge
      pq.pop();
      
      int count;
      count = h1->count + h2->count; // sum count for the new parent node
      HCNode* parent = new HCNode(count, 0); // create a new merge node
      h1->p = parent;         // insert this node into the tree
      h2->p = parent;
      parent->c0 = h1;        // put smallest value in to left-sub tree
      parent->c1 = h2;
      pq.push(parent);        // add this node back to queue
    }
    root = pq.top();  // set top node to root, include one node case
  }
}

void HCTree::encode(byte symbol, BitOutputStream& out) const
{
  HCNode* curNode = leaves[(int)symbol]; // find the correct node
  stack<int> s;            // create a stack for reverse the order
  
  while(curNode != root)
  {
    if(curNode == curNode->p->c0) // check the node represent 0 or 1
      s.push(0);
    else s.push(1);
    curNode = curNode->p; // traverse from bottom to top
  }
  while(s.size() != 0)    // write binary code one by one
  {                       // last in, first out. top is the last insert
    out.writeBit(s.top());
    s.pop();
  }
}

int HCTree::decode(BitInputStream& in) const
{
  if(root != nullptr)       // check if it is empty case
  {
    HCNode* curNode = root; // search from top to down
    while((curNode->symbol == 0)&&(curNode != leaves[0])) 
    {                              // find the meaningful node
    
      int read = in.readBit();     // read bit by bit
      if(read == 0)                // check curNode should go left or right
        curNode = curNode->c0;
      else curNode = curNode->c1;
    }
    return curNode->symbol; // return the symbol value
  }
}

