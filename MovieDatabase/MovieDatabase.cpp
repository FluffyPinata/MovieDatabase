#include <iostream>
//#include "BinarySearchTree.h"
#include "Actor.h"
#include "BSTree.h"
#include "BSTree.hpp"

int main()
{
	Actor a, b, c;
	a.setName("Toast");
	b.setName("Why");
	c.setName("Suffering");
	BSTree<Actor, string > *tree = new BSTree<Actor, string>;
	tree->addNode(a.getName(), a);
	tree->addNode(b.getName(), b);
	tree->addNode(c.getName(), c);
	tree->printInorder();

    return 0; 
}

