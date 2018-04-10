#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

template <class T> 
class BinarySearchTree {
private:
	//Each node contains a piece of data (some class), as well as pointers to a left and right node.
	//By default both pointers are null.
	struct BSTNode {
		T data;
		BSTNode * left = nullptr;
		BSTNode * right = nullptr;
	};

	//The very first node
	BSTNode * rootNode;
public:
	BinarySearchTree();
	void deleteTree(BSTNode * nodeToDelete);
};

#endif
