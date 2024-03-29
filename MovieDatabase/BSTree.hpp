//To be used in conjunction with BSTree.h and Node.h
//When you modify this, please add your name and list any changes that you made
//A few member functions have been left blank so you, the student can implemement

/*Template Directions: #include "BSTREEInt.hpp"
but do NOT compile it (or add it to the project)*/
#include "BSTree.h"
#include <fstream>
#include <iostream>

//Created by Gabriel Jones

// Constructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::BSTree() {
	root = nullptr;
}

// Destructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::~BSTree() {
    if (root !=nullptr)
        freeNode(root);
}

// Free the node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::freeNode(Node<DATATYPE, KEYTYPE> * leaf)
{
	//Student must fill in
	if (leaf != nullptr) {
		//Recursively dives down left and right subtrees, deleting the nodes until it reaches nullptr
		freeNode(leaf->Left());
		freeNode(leaf->Right());

		delete leaf;
		leaf = nullptr;
	}

}

// Add a node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, DATATYPE &data)
{
	if (Root() == nullptr)
	{
		Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
		newNodePtr->setKey(key);
		newNodePtr->setData(data);
		root = newNodePtr;
		root->setParent(root);

	}
	else
		addNode(key, root, data);
}

// Add a node (private)
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> * leaf, DATATYPE& data) {
	//Student must fill in
	//Don't forget to set your key, Parent, then left or right
	//Based on the case you use you will addNode recursively to the left or right
 
	//First check if root is null
	if (Root() == nullptr)
	{
		// make a new node
		//set the key and data
		//set the root
		Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
		newNodePtr->setKey(key);
		newNodePtr->setData(data);
		root = newNodePtr;
		root->setParent(root);
	}
	else { //Otherwise
		//Check to see if the key is < the leaf's key
			// if left is not null then
				//Add the node to the left (recursively)
				// Otherwise make a new node and attach it to the left
		if (key < leaf->Key()) {
			if (leaf->Left() == nullptr) {
				Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
				newNodePtr->setKey(key);
				newNodePtr->setData(data);
				leaf->setLeft(newNodePtr);
				leaf->Left()->setParent(leaf);
			}
			else {
				addNode(key, leaf->Left(), data);
			}
		} 

		//Check to see if the key >= leaf's key
			// if leaf's right is not null then
				//Add the node to the right (recursively)
			// Otherwise make new node and attach it to the right
		else if (key >= leaf->Key()) {
			if (leaf->Right() == nullptr) {
				Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
				newNodePtr->setKey(key);
				newNodePtr->setData(data);
				leaf->setRight(newNodePtr);
				leaf->Right()->setParent(leaf);
			}
			else {
				addNode(key, leaf->Right(), data);
			}
		}
	}
}

template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key)
{
	return findNode(key, root);
}

// Find a node
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> * node)
{
	//Student must fill in
	// trap nullptr first in case we've hit the end unsuccessfully.
	if (node == nullptr) {
		return nullptr;
	}
	// success base case
	if (key == node->Key()) {
		return node;
	}
	else {
		if (key < node->Key()) {
			return findNode(key, node->Left());
		}
		else if (key > node->Key()) {
			return findNode(key, node->Right());
		}
	}
	//Greater than (Right), Less than (Left)
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder()
{
	printInorder(root);
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder(Node<DATATYPE, KEYTYPE> * node)
{
	//Student must fill in.  Use recursive algorithm.
	if (node == nullptr) { //base case of nullptr
		return;
	}
	printInorder(node->Left()); //Dive down the left side of the tree first since those are the lowest values
	std::cout << node->Data() << std::endl; //note.. should this be data or key?
	printInorder(node->Right()); //Dive down the right side last since they're the largest values
	//Note that this prints using an Inorder, Depth-first search
	//but you may want to do something else when "visiting" the node....
	//like moving visited data to another datastructure
	//Don't forget your base case!

}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::print(ostream & out, const DATATYPE & data)
{
	out << data.number << "\t" << data.name << endl;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::deleteNode(KEYTYPE key)
{
	setRoot(deleteNode(Root(), key));
}

//deleteNode (Private)
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::deleteNode(Node<DATATYPE, KEYTYPE> * aRoot,KEYTYPE value)
{
   
	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */
	
	// base case
	if (aRoot == nullptr) return aRoot;

	// If the key to be deleted is smaller than the aRoot's key,
	// then it lies in left subtree
	if (value < aRoot->Key())
		aRoot->setLeft(deleteNode(aRoot->Left(), value));

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (value > aRoot->Key())
		aRoot->setRight(deleteNode(aRoot->Right(), value));

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
		if (aRoot->Left() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Right();
			delete aRoot;	
			return temp;
		}
		else if (aRoot->Right() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Left();
			delete aRoot;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		Node<DATATYPE, KEYTYPE> * temp = min(aRoot->Right());

		// Copy the inorder successor's content to this node
		aRoot->setKey(temp->Key());
		aRoot->setData(temp->Data());

		// Delete the inorder successor
		aRoot->setRight(deleteNode(aRoot->Right(), temp->Key()));
	}
	return aRoot;
}


// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::min(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * current = node;

	/* loop down to find the leftmost leaf */
	while (current->Left() != nullptr)
		current = current->Left();

	return current;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::max(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Right())
		tempNode = max(node->Right());
	else
		tempNode = node;

	return tempNode;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::writeToFile(std::ofstream &outfile) {
	writeToFile(outfile, root);
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::writeToFile(std::ofstream &outfile, Node<DATATYPE, KEYTYPE> * node) {
	if (node == nullptr) { //base case of nullptr
		return;
	}
	writeToFile(outfile, node->Left()); //Dive down the left side of the tree first since those are the lowest values
	outfile << node->Data(); //Print data to the file
	writeToFile(outfile, node->Right()); //Dive down the right side last since they're the largest values
}

