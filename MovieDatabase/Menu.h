#ifndef MENU_H
#define MENU_H

#include "BSTree.h"
#include "BSTree.hpp"
#include "Actor.h"
#include "Movie.h"
#include <vector>

//Created by Gabriel Jones

//Think of these enums as just numbers. They let the program choose which tree is currently being used since after a sort it gets changed to the keytype of the sort.
//This is neccessary since you don't want to add a string key to a integer tree for example
enum currentTreeActor { actName, actAward, actFilm, actYear, actWinner };
enum currentTreeMovie { movName, movGenre1, movGenre2, movRelease, movSynopsis, movYear, movNominations, movDuration, movMetacritic, movRating };

class Menu {
private:
	currentTreeActor cTa = actName; //used for selecting which tree to operate on after a potential sort
	currentTreeMovie cTm = movName;
	std::vector<Actor> actorData; //This is used for searching data, since it's faster than doing it on the tree (keytype usually doesn't match up with search parameter)
	std::vector<Actor> tempSortActorData; //used for saving temp data during searches
	std::vector<Movie> movieData;
	std::vector<Movie> tempSortMovieData;
	//Different trees used for sorting
	BSTree<Actor, string> *actorTree;
	BSTree<Actor, int> *actorTreeInt;
	BSTree<Actor, bool> *actorTreeBool;
	BSTree<Movie, string> *movieTree;
	BSTree<Movie, int> *movieTreeInt;
	BSTree<Movie, double> *movieTreeDouble;

public:
	Menu();
	//Each pair of functions works virtually the same way for actor and movie, just with slightly different data inputs since the data they store is different
	void runMenu();
	void readActors();
	void readMovies();
	void printInOrderActors();
	void printInOrderMovies();
	void addRecordActors();
	void addRecordMovies();
	bool searchActor();
	bool searchMovie();
	void sortTreeActor();
	void sortTreeMovie();
	void exactSearchActor(int choice);
	void exactSearchMovie(int choice);
	void partialSearchActor(int choice);
	void partialSearchMovie(int choice);
	void modifyRecordActor(Actor &a);
	void modifyRecordMovie(Movie &m);
	void deleteRecordActor(Actor a);
	void deleteRecordMovie(Movie m);
	void deleteCurrentTree(); //Actors
	void deleteCurrentTreeMovie(); //Movies
	void editDeleteRecords(); //Actors
	void editDeleteRecordsMovie();
};

#endif