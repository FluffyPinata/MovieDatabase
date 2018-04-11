#ifndef MENU_H
#define MENU_H

#include "BSTree.h"
#include "BSTree.hpp"
#include "Actor.h"

class Menu {
private:
	BSTree<Actor, string> *actorTree;

public:
	Menu();
	void readActors();
};

#endif