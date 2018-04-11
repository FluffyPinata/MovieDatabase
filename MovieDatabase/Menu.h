#ifndef MENU_H
#define MENU_H

#include "BSTree.h"
#include "BSTree.hpp"
#include "Actor.h"
#include "Movie.h"

class Menu {
private:
	BSTree<Actor, string> *actorTree;
	BSTree<Movie, string> *movieTree;

public:
	Menu();
	void readActors();
	void readMovies();
	void printInOrderActors();
	void printInOrderMovies();
};

#endif