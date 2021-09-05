#include <stdio.h>
#include <iostream>
#include<list>
using namespace std;
typedef int ElementType;

#pragma once
class LazyBST
{
private:
	class Node
	{
	public:
		ElementType data;
		Node * L;
		Node * R;
		bool tagged;

		Node() : L(0), R(0), tagged(0)
		{
		}

		Node(ElementType item) : data(item), L(0), R(0), tagged(0)
		{
		}
	};
	typedef Node* NodePointer;

	int heightPriv(NodePointer root);
	/*--------------------------------------------------------------------
	 Returns the height of the tree including nodes tagged as erased.
	---------------------------------------------------------------------*/
	void search(ElementType item, bool& found, NodePointer& locptr, NodePointer& parent);
	/*--------------------------------------------------------------------
	 Search for item in the entire BST.
	---------------------------------------------------------------------*/
	void clearPriv(NodePointer root);
	/*--------------------------------------------------------------------
	 Delete all the nodes in the tree.
	---------------------------------------------------------------------*/
	void cleanPriv(NodePointer root);
	/*--------------------------------------------------------------------
	 Delete only nodes tagged as deleted (erased).
	---------------------------------------------------------------------*/
	void remove(ElementType item);
	/*--------------------------------------------------------------------
	 Removes given item.
	---------------------------------------------------------------------*/

public:

	LazyBST();
	/*--------------------------------------------------------------------
	 Default constructor: builds an empty Tree object.
	 --------------------------------------------------------------------*/
	bool empty();
	/*--------------------------------------------------------------------
	 Return true if the tree is empty (the size is 0).
	 --------------------------------------------------------------------*/
	int size();
	/*--------------------------------------------------------------------
	 Returns the number of nodes in the tree not including nodes tagged as erased.
	 --------------------------------------------------------------------*/
	int height();
	/*--------------------------------------------------------------------
	 Returns the funtion heightPriv recursivly.
    ---------------------------------------------------------------------*/
	bool member(ElementType const& item);
	/*--------------------------------------------------------------------
	 Return true if the argument is in the tree and not tagged as erased and false otherwise.
	---------------------------------------------------------------------*/
	ElementType front();
	/*--------------------------------------------------------------------
	 Return the minimum non-erased object of this tree by calling front on the root node.
	---------------------------------------------------------------------*/
	ElementType back();
	/*--------------------------------------------------------------------
	 Return the maximum non-erased object of this tree by calling back on the root node.
	---------------------------------------------------------------------*/
	void breadth_first_traversal();
	/*--------------------------------------------------------------------
	 Perform a breadh-first traversal. (NLR)
	---------------------------------------------------------------------*/
	bool insert(ElementType item);
	/*--------------------------------------------------------------------
	 Insert the new object into the tree: 
	 If the object is already in the tree and not tagged as erased, return false and do nothing; 
	 if the object is already in the tree but tagged as erased, untag it and return true; 
	 if the object is not in the tree, create a new leaf node in the appropriate location and return true. 
	 If the root node is nullptr, this requires the creation of a new root node; 
	 otherwise, the corresponding function is called on the root node. 
	---------------------------------------------------------------------*/
	bool erase(ElementType item);
	/*--------------------------------------------------------------------
	 Removes the object from the tree: 
	 If the object is not already in the tree, return false;
	 if the object is in the tree but tagged as erased, return false;
	 if the object is in the tree and not tagged as erased, tag it as erased and return true.
	 If the root node is nullptr, all that is done is that false is returned; 
	 otherwise, the corresponding function is called on the root node.
	---------------------------------------------------------------------*/
	void clear();
	/*--------------------------------------------------------------------
	 Returns the function clearPriv recursivly.
	---------------------------------------------------------------------*/
	void clean();
	/*--------------------------------------------------------------------
	 Returns the function cleanPriv recursivly.
	---------------------------------------------------------------------*/
	void print2D();
	void print2DPriv(NodePointer root, int space);

private:
	NodePointer root;
	int mySize;
	int taggedSize;
	list<NodePointer> deleted;
};
