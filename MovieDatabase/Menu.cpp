#include "Menu.h"
#include <fstream>
#include <sstream>

Menu::Menu() {
	actorTree = new BSTree<Actor, string>();
	actorTreeInt = new BSTree<Actor, int>();
	actorTreeBool = new BSTree<Actor, bool>();
	movieTree = new BSTree<Movie, string>();
}

void Menu::runMenu() {
	bool keepGoing = true;
	while (keepGoing) {
		int option;
		std::cout << "What option would you like to choose? (type the number)" << std::endl;
		std::cout << "1. Read in actor list." << std::endl;
		std::cout << "2. Read in movie list." << std::endl;
		std::cout << "3. Add an actor to the actor list." << std::endl;
		std::cout << "4. Add a movie to the movie list." << std::endl;
		std::cout << "5. Display the actor list by name." << std::endl;
		std::cout << "6. Display the movie list by name." << std::endl;
		std::cout << "7. Search and modify an actor." << std::endl;
		std::cout << "10. Quit the game." << std::endl << std::endl;

		std::cin >> option;

		switch (option) {
		case 1:
			std::cout << "Reading in the actor list..." << std::endl;
			readActors();
			break;
		case 2:
			std::cout << "Reading in the movie list..." << std::endl;
			readMovies();
			break;
		case 3:
			addRecordActors();
			break;
		case 4:
			addRecordMovies();
			break;
		case 5:
			printInOrderActors();
			break;
		case 6:
			printInOrderMovies();
			break;
		case 7:
			searchAndModifyActor();
			break;
		case 10:
			std::cout << "Exiting the program..." << std::endl;
			keepGoing = false;
			break;
		}
	}
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

		actorData.push_back(tempActor);
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

		name = name.substr(1, name.size());

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

		movieData.push_back(tempMovie);
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

	actorData.push_back(newActor);
	actorTree->addNode(name, newActor);
}

void Menu::addRecordMovies() {
	std::cin.ignore();
	std::cout << "Please enter in the following information for a movie:" << std::endl;
	std::string name, genre1, genre2, release, synopsis;
	int year, nominations, duration, metacritic;
	double rating;

	std::cout << "Movie name: " << std::endl;
	getline(std::cin, name);

	std::cout << "Movie's 1st genre: " << std::endl;
	getline(std::cin, genre1);

	std::cout << "Movie's 2nd genre: " << std::endl;
	getline(std::cin, genre2);

	std::cout << "Movie's release month: " << std::endl;
	getline(std::cin, release);

	std::cout << "Movie's synopsis: " << std::endl;
	getline(std::cin, synopsis);

	std::cout << "Year the movie came out in: " << std::endl;
	std::cin >> year;

	std::cout << "Number of nominations: " << std::endl;
	std::cin >> nominations;

	std::cout << "Duration in minutes: " << std::endl;
	std::cin >> duration;

	std::cout << "Metacritic score: " << std::endl;
	std::cin >> metacritic;

	std::cout << "Movie rating: " << std::endl;
	std::cin >> rating;

	Movie newMovie(name, genre1, genre2, release, synopsis, year, nominations, duration, metacritic, rating);

	movieData.push_back(newMovie);
	movieTree->addNode(name, newMovie);
}

bool Menu::searchAndModifyActor() { //not working currently
	std::cin.ignore();
	std::cout << "Which actor would you like to search for? Please enter a name." << std::endl;
	std::string searchName, newName;
	getline(std::cin, searchName);

	Node<Actor, std::string> *foundNodePtr = actorTree->findNode(searchName);

	if (foundNodePtr != nullptr) {
		std::cout << "Please enter a new name for the actor:" << std::endl;
		getline(std::cin, newName);

		return true;
	}
	else {
		std::cout << "We couldn't find an actor with that name." << std::endl;
		return false;
	}
}


void Menu::sortTreeActor() {
	std::cout << "Which parameter would you like to sort the actor tree by?" << std::endl;
	std::cout << "1. Name" << std::endl;
	std::cout << "2. Award" << std::endl;
	std::cout << "3. Film" << std::endl;
	std::cout << "4. Year" << std::endl;
	std::cout << "5. Winner?" << std::endl;

	int selection = 0;
	std::cin >> selection;

	switch (selection) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		break;
	}

}




