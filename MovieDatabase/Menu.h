#ifndef MENU_H
#define MENU_H

#include "BSTree.h"
#include "BSTree.hpp"
#include "Actor.h"
#include "Movie.h"
#include <vector>

enum currentTreeActor { actName, actAward, actFilm, actYear, actWinner };

class Menu {
private:
	currentTreeActor cTa = actName; //used for selecting which tree to operate on after a potential sort
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