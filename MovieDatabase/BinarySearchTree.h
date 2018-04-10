#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

template <class T> 
class BinarySearchTree {
private:
	struct BSTNode {
		T data;
		BSTNode * left;
		BSTNode * right;
	};

	BSTNode * rootNode;
public:
	BinarySearchTree();
};

#endif
