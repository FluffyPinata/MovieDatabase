#include <iostream>
//#include "BinarySearchTree.h"
#include "Actor.h"
#include "functions.h"

int main()
{
	BSTree<Actor, string > *tree = new BSTree<Actor, string>;
	readActors(tree);
	tree->printInorder();

    return 0; 
}

