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

template <class T>
BinarySearchTree<T>::BinarySearchTree() {
	rootNode = nullptr;
}

template <class T>
void BinarySearchTree<T>::deleteTree(BSTNode * nodeToDelete) {
	if (nodeToDelete == nullptr) { //You've reached the end of a tree
		return; //Stop what we're doing.
	}
	//Traverse and delete both subtrees recursively.
	deleteTree(nodeToDelete->left);
	deleteTree(nodeToDelete->right);
	//delete the current node
	delete nodeToDelete;
}

#endif
