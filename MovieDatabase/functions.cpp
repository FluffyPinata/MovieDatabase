#include "functions.h"
#include <fstream>
#include <sstream>

void readActors(BSTree<Actor, string > *&tree) {
	std::ifstream infile("actor-actress.csv");
	std::string junk, line;
	getline(infile, junk); 

	while (getline(infile, line)) {
		std::stringstream ss(line);
		std::string name, award, film, yearS, winnerS; //we need to convert the last two to int and bool
		
		getline(ss, yearS, ',');
		getline(ss, award, ',');
		getline(ss, winnerS, ',');
		getline(ss, name, ',');
		getline(ss, film, ',');

		int year;
		bool winner;
		if (winnerS == "1") {
			winner = true;
		}
		else {
			winner = false;
		}

		year = stoi(yearS);

		Actor tempActor(year, name, award, film, winner);

		tree->addNode(name, tempActor);
	}
}