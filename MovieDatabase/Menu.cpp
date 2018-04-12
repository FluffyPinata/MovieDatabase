#include "Menu.h"
#include <fstream>
#include <sstream>

Menu::Menu() {
	actorTree = new BSTree<Actor, string>();
	movieTree = new BSTree<Movie, string>();
}

void Menu::readActors() {
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

		actorTree->addNode(name, tempActor);
	}
	infile.close();
}

void Menu::readMovies() {
	std::ifstream infile("pictures.csv");
	std::string junk, line;
	getline(infile, junk);

	while (getline(infile, line)) {
		std::stringstream ss(line);
		std::string name, genre1, genre2, release, synopsis, yearS, nominationsS, durationS, metacriticS, ratingS;
		int year, nominations, duration, metacritic;
		double rating;

		getline(ss, name, ',');
		getline(ss, yearS, ',');
		getline(ss, nominationsS, ',');
		getline(ss, ratingS, ',');
		getline(ss, durationS, ',');
		getline(ss, genre1, ',');
		getline(ss, genre2, ',');
		getline(ss, release, ',');
		getline(ss, metacriticS, ',');
		getline(ss, synopsis, ',');

		year = stoi(yearS);
		try {
			nominations = stoi(nominationsS);
		}
		catch (std::invalid_argument) {
			//std::cout << "No nominations entered, defaulting to 0." << std::endl;
			nominations = 0;
		}
		duration = stoi(durationS);
		try {
			metacritic = stoi(metacriticS);
		}
		catch (std::invalid_argument) {
			//std::cout << "No metacritic score, defaulting to -1." << std::endl;
			metacritic = -1;
		}
		rating = stod(ratingS);

		Movie tempMovie(name, genre1, genre2, release, synopsis, year, nominations, duration, metacritic, rating);

		movieTree->addNode(name, tempMovie);
	}
	infile.close();
}

void Menu::printInOrderActors() {
	actorTree->printInorder();
}

void Menu::printInOrderMovies() {
	movieTree->printInorder();
}

void Menu::addRecordActors() {
	std::cout << "Please enter in the following information for an actor/actress and their nomination:" << std::endl;
	int year, winnerI;
	std::string award, name, film;
	bool winner;
	
	std::cout << "Year of nomination: " << std::endl;
	std::cin >> year;
	std::cin.ignore();

	std::cout << "What award were they nominated for?" << std::endl;
	getline(std::cin, award);

	std::cout << "What is their name?" << std::endl;
	getline(std::cin, name);

	std::cout << "What film did they star in?" << std::endl;
	getline(std::cin, film);

	std::cout << "Did they win the award? (Type 1 for yes, 0 for no)" << std::endl;
	std::cin >> winnerI;

	if (winnerI == 1)
		winner = true;
	else if (winnerI == 0)
		winner = false;

	Actor newActor(year, name, award, film, winner);

	actorTree->addNode(name, newActor);
}


