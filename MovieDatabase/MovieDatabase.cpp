#include <iostream>
//#include "BinarySearchTree.h"
#include "Actor.h"
#include "BSTree.h"
#include "BSTree.hpp"
#include "functions.h"

int main()
{
	Actor a, b, c, d;
	a.setName("Toast");
	b.setName("Why");
	c.setName("Suffering");
	d.setName("Apple");
	BSTree<Actor, string > *tree = new BSTree<Actor, string>;
	tree->addNode(a.getName(), a);
	tree->addNode(b.getName(), b);
	tree->addNode(c.getName(), c);
	tree->addNode(d.getName(), d);
	tree->printInorder();

    return 0; 
}

