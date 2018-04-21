#ifndef MENU_H
#define MENU_H

#include "BSTree.h"
#include "BSTree.hpp"
#include "Actor.h"
#include "Movie.h"

class Menu {
private:
	enum currentTreeActor { actName, actAward, actFilm, actYear, actWinner };
	BSTree<Actor, string> *actorTree;
	BSTree<Actor, int> *actorTreeInt;
	BSTree<Actor, bool> *actorTreeBool;
	BSTree<Movie, string> *movieTree;

public:
	Menu();
	void runMenu();
	void readActors();
	void readMovies();
	void printInOrderActors();
	void printInOrderMovies();
	void addRecordActors();
	void addRecordMovies();
	bool searchAndModifyActor();
	void sortTreeActor();
};

#endif