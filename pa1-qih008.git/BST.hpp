/*
  Name: Qing Huang
  Project: PA1
  Date: 7/6/2014
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    clear();      // clear will take care of deleting all nodes in BST
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) {
    BSTNode<Data>* curNode = nullptr;
    BSTNode<Data>* newNode = nullptr;
    bool insert = false;

    if(root == nullptr) // empty BST
    {
      newNode = new BSTNode<Data>(item);
      root = newNode;   // create a root
      insert = true;    // insert a node
      isize++;          //increase counter
    }
    else               // non-empty BST
    {
      curNode = root;
      while(newNode == nullptr)
      {
        if(curNode->data > item) // cur value bigger than new value
	{                        // put new node in left sub-tree
	  if(curNode->left == nullptr)
          {
	    newNode = new BSTNode<Data>(item); // create new node
	    newNode->parent = curNode;// assign parent
	    curNode->left = newNode;  // put new node in left sub-tree
	    insert = true;
	    isize++;
	  }
	  else curNode = curNode->left;  // recursive step
	}
        else if(curNode->data < item) // put new node in the right sub-tree
	{                         // same with above
          if(curNode->right == nullptr)
	  {
	    newNode = new BSTNode<Data>(item);
	    newNode->parent = curNode; 
	    curNode->right = newNode;
	    insert = true;
	    isize++;
	  }
	  else curNode = curNode->right;
	}
	else newNode = curNode;  // exist the same value
      }
    }
    return std::make_pair(BST<Data>::iterator(newNode),insert);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const {
    BSTNode<Data>* curNode = root;
    while(curNode != nullptr) //if not find, curNode=nullptr
    {
      if(curNode->data > item) 
        curNode = curNode->left; // item less than curNode,search left
      else if(curNode->data < item) 
        curNode = curNode->right;// item bigger than curNode, search right
      else break;  //find item
    }
    return typename BST<Data>::iterator(curNode); //if not find, the 
                                            //end iterator would be nullptr
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear() {
    clearNode(root);
    root = nullptr;
    isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return root == nullptr;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
    BSTNode<Data>* first = root;//first item in in-order BST is left most child
                                //find left most child
    while((first != nullptr) && (first->left != nullptr))
      first = first->left;

    return typename BST<Data>::iterator(first);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

private:
  /* helper function of clear() */
  void clearNode(BSTNode<Data>* node) {
    if( node != nullptr)
    {
      if(node->left != nullptr)
        clearNode(node->left); // recursion to traverse the tree and delete
      if(node->right != nullptr) // everything
        clearNode(node->right);
      delete node;
    }
  }
};


#endif //BST_HPP
