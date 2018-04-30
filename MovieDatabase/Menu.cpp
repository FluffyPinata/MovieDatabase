#include "Menu.h"
#include <fstream>
#include <sstream>

Menu::Menu() {
	actorTree = new BSTree<Actor, string>();
	actorTreeInt = new BSTree<Actor, int>();
	actorTreeBool = new BSTree<Actor, bool>();
	movieTree = new BSTree<Movie, string>();
	movieTreeInt = new BSTree<Movie, int>();
	movieTreeDouble = new BSTree<Movie, double>();
}

void Menu::runMenu() {
	std::ofstream outfile("output.csv");
	bool keepGoing = true;
	while (keepGoing) {
		int option;
		std::cout << "What option would you like to choose? (type the number)" << std::endl;
		std::cout << "1. Read in actor list." << std::endl;
		std::cout << "2. Read in movie list." << std::endl;
		std::cout << "3. Add an actor to the actor list." << std::endl;
		std::cout << "4. Add a movie to the movie list." << std::endl;
		std::cout << "5. Display the actor list by current key." << std::endl;
		std::cout << "6. Display the movie list by current key" << std::endl;
		std::cout << "7. Search and modify an actor." << std::endl;
		std::cout << "8. Sort actor tree." << std::endl;
		std::cout << "9. Write actor tree to file." << std::endl;
		std::cout << "10. Quit the game." << std::endl;
		std::cout << "11. Write movie tree to file." << std::endl;

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
			searchActor();
			break;
		case 8:
			sortTreeActor();
			break;
		case 9:
			outfile << "YEAR,AWARD,WINNER,NAME,FILM" << std::endl;
			if ((cTa == actName) || (cTa == actAward) || (cTa == actFilm)) {
				actorTree->writeToFile(outfile);
			}
			else if (cTa == actYear) {
				actorTreeInt->writeToFile(outfile);
			}
			else {
				actorTreeBool->writeToFile(outfile);
			}
			break;
		case 10:
			std::cout << "Exiting the program..." << std::endl;
			keepGoing = false;
			break;
		case 11:
			outfile << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis" << std::endl;
			if ((cTm == movName) || (cTm == movGenre1) || (cTm == movGenre2) || (cTm == movRelease) || (cTm == movSynopsis)) {
				movieTree->writeToFile(outfile);
			}
			else if ((cTm == movYear) || (cTm == movNominations) || (cTm == movDuration) || (cTm == movMetacritic)) {
				movieTreeInt->writeToFile(outfile);
			}
			else if (cTm == movRating) {
				movieTreeDouble->writeToFile(outfile);
			}
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
		if (cTa == actName)
			actorTree->addNode(name, tempActor);
		else if (cTa == actAward)
			actorTree->addNode(award, tempActor);
		else if (cTa == actFilm)
			actorTree->addNode(film, tempActor);
		else if (cTa == actYear)
			actorTreeInt->addNode(year, tempActor);
		else
			actorTreeBool->addNode(winner, tempActor);
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
		//sorry this is ugly
		if (cTm == movName)
			movieTree->addNode(name, tempMovie);
		else if (cTm == movGenre1)
			movieTree->addNode(genre1, tempMovie);
		else if (cTm == movGenre2)
			movieTree->addNode(genre2, tempMovie);
		else if (cTm == movRelease)
			movieTree->addNode(release, tempMovie);
		else if (cTm == movSynopsis)
			movieTree->addNode(synopsis, tempMovie);
		else if (cTm == movYear)
			movieTreeInt->addNode(year, tempMovie);
		else if (cTm == movNominations)
			movieTreeInt->addNode(nominations, tempMovie);
		else if (cTm == movDuration)
			movieTreeInt->addNode(duration, tempMovie);
		else if (cTm == movMetacritic)
			movieTreeInt->addNode(metacritic, tempMovie);
		else if (cTm == movRating)
			movieTreeDouble->addNode(rating, tempMovie);
	}
	infile.close();
}

void Menu::printInOrderActors() {
	if ((cTa == actName) || (cTa == actAward) || (cTa == actFilm)) {
		actorTree->printInorder();
	}
	else if (cTa == actYear) {
		actorTreeInt->printInorder();
	}
	else {
		actorTreeBool->printInorder();
	}
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
	if (cTa == actName)
		actorTree->addNode(name, newActor);
	else if (cTa == actAward)
		actorTree->addNode(award, newActor);
	else if (cTa == actFilm)
		actorTree->addNode(film, newActor);
	else if (cTa == actYear)
		actorTreeInt->addNode(year, newActor);
	else
		actorTreeBool->addNode(winner, newActor);
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

	movieData.push_back(newMovie); //one of the string trees
	if (cTm == movName)
		movieTree->addNode(name, newMovie);
	else if (cTm == movGenre1)
		movieTree->addNode(genre1, newMovie);
	else if (cTm == movGenre2)
		movieTree->addNode(genre2, newMovie);
	else if (cTm == movRelease)
		movieTree->addNode(release, newMovie);
	else if (cTm == movSynopsis)
		movieTree->addNode(synopsis, newMovie);
	else if (cTm == movYear)
		movieTreeInt->addNode(year, newMovie);
	else if (cTm == movNominations)
		movieTreeInt->addNode(nominations, newMovie);
	else if (cTm == movDuration)
		movieTreeInt->addNode(duration, newMovie);
	else if (cTm == movMetacritic)
		movieTreeInt->addNode(metacritic, newMovie);
	else if (cTm == movRating)
		movieTreeDouble->addNode(rating, newMovie);
		
}

bool Menu::searchActor() { //not working currently
	std::cin.ignore();
	int fieldChoice = 0;
	std::cout << "Which field would you like to search? (type the number)" << std::endl;
	std::cout << "1. Name" << std::endl;
	std::cout << "2. Award" << std::endl;
	std::cout << "3. Film" << std::endl;
	std::cout << "4. Year" << std::endl;


	std::cin >> fieldChoice;
	switch (fieldChoice) {
	case 1:
		exactSearchActor(fieldChoice);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

	//std::cout << "What would you like to search for?" << std::endl;
	return true;
}


void Menu::sortTreeActor() {
	//Ask for which key the user would like to sort the tree by.
	std::cout << "Which parameter would you like to sort the actor tree by?" << std::endl;
	std::cout << "1. Name" << std::endl;
	std::cout << "2. Award" << std::endl;
	std::cout << "3. Film" << std::endl;
	std::cout << "4. Year" << std::endl;
	std::cout << "5. Winner?" << std::endl;

	int selection = 0;
	std::cin >> selection;

	//Based on which tree is currently being used, that tree will have it's memory freed and then a 
	//new one will be filled with the selected key.
	switch (selection) {
	case 1:
		deleteCurrentTree();
		cTa = actName;
		for (int i = 0; i < actorData.size(); i++) {
			actorTree->addNode(actorData[i].getName(), actorData[i]);
		}
		break;
	case 2:
		deleteCurrentTree();
		cTa = actAward;
		for (int i = 0; i < actorData.size(); i++) { // n complexity
			actorTree->addNode(actorData[i].getAward(), actorData[i]);
		}
		break;
	case 3:
		deleteCurrentTree();
		cTa = actFilm;
		for (int i = 0; i < actorData.size(); i++) { // n complexity
			actorTree->addNode(actorData[i].getFilm(), actorData[i]);
		}
		break;
	case 4:
		deleteCurrentTree();
		cTa = actYear;
		for (int i = 0; i < actorData.size(); i++) { // n complexity
			actorTreeInt->addNode(actorData[i].getYear(), actorData[i]);
		}
		break;
	case 5:
		deleteCurrentTree();
		cTa = actWinner;
		for (int i = 0; i < actorData.size(); i++) { // n complexity
			actorTreeBool->addNode(actorData[i].getWinner(), actorData[i]);
		}
		break;
	default:
		break;
	}

}

void Menu::deleteCurrentTree() { //picks the current stored tree and deletes it
	if ((cTa == actName) || (cTa == actAward) || (cTa == actFilm)) {
		delete actorTree;
		actorTree = new BSTree<Actor, string>();
	}
	else if (cTa == actYear) {
		delete actorTreeInt;
		actorTreeInt = new BSTree<Actor, int>();
	}
	else {
		delete actorTreeBool;
		actorTreeBool = new BSTree<Actor, bool>();
	}
}

void Menu::exactSearchActor(int choice) {
	std::string searchString;
	int searchYear;
	std::cin.ignore();
	switch (choice) {
		case 1:
			std::cout << "Please enter the string you'd like to perform an exact search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) {
				if (actorData[i].getName() == searchString) {
					modifyRecordActor(actorData[i]);
				}
			}
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
	}
}

void Menu::modifyRecordActor(Actor &a) {
	//Initially delete the node from the list 
	if (cTa == actName) {
		actorTree->deleteNode(a.getName());
	}
	else if (cTa == actAward) {
		actorTree->deleteNode(a.getAward());
	}
	else if (cTa == actFilm) {
		actorTree->deleteNode(a.getFilm());
	}
	else if (cTa == actYear) {
		actorTreeInt->deleteNode(a.getYear());
	}
	else {
		actorTreeBool->deleteNode(a.getWinner());
	}

	//Obtain all the information about the new node from the user and modify our current data
	std::string choice;
	int modifierI;
	std::string modifier;
	std::cout << "Would you like to change the name of the actor?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		a.setName(modifier);
	}
	std::cout << "Would you like to change the award of the actor?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		a.setAward(modifier);
	}
	std::cout << "Would you like to change the film of the actor?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		a.setFilm(modifier);
	}
	std::cout << "Would you like to change the year of the actor?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		std::cin >> modifierI;
		a.setYear(modifierI);
	}


	//Pick which tree is currently active and re-add the modified one to the list.
	if (cTa == actName) {
		actorTree->addNode(a.getName(), a);
	}
	else if (cTa == actAward) {
		actorTree->addNode(a.getAward(), a);
	}
	else if (cTa == actFilm) {
		actorTree->addNode(a.getFilm(), a);
	}
	else if (cTa == actYear) {
		actorTreeInt->addNode(a.getYear(), a);
	}
	else {
		actorTreeBool->addNode(a.getWinner(), a);
	}
}

bool Menu::isContained() {
	return true;
}



