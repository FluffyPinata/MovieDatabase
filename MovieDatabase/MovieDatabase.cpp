#include <iostream>
//#include "BinarySearchTree.h"
#include "Actor.h"

int main()
{
	Actor a;
	Actor b;
	Actor c;
	a.setName("Toast");
	b.setName("Why");
	c.setName("Suffering");
	BinarySearchTree<Actor> actorTree;
	actorTree.insert(a);
	std::cout << "Hello!" << std::endl;
    return 0; 
}

