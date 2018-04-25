#ifndef MENU_H
#define MENU_H

#include "BSTree.h"
#include "BSTree.hpp"
#include "Actor.h"
#include "Movie.h"
#include <vector>

enum currentTreeActor { actName, actAward, actFilm, actYear, actWinner };
enum currentTreeMovie { movName, movGenre1, movGenre2, movRelease, movSynopsis, movYear, movNominations, movDuration, movMetacritic, movRating };

class Menu {
private:
	currentTreeActor cTa = actName; //used for selecting which tree to operate on after a potential sort
	currentTreeMovie cTm = movName;
	std::vector<Actor> actorData;
	std::vector<Movie> movieData;
	//Different trees used for sorting
	BSTree<Actor, string> *actorTree;
	BSTree<Actor, int> *actorTreeInt;
	BSTree<Actor, bool> *actorTreeBool;
	BSTree<Movie, string> *movieTree;
	BSTree<Movie, int> *movieTreeInt;
	BSTree<Movie, double> *movieTreeDouble;

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
	void deleteCurrentTree();
};

#endif