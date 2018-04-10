#include "BinarySearchTree.h"

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