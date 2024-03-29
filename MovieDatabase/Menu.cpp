#include "Menu.h"
#include <fstream>
#include <sstream>

//Created by Gabriel Jones

Menu::Menu() {
	//Initialize all the trees here since we can't do it the header.
	actorTree = new BSTree<Actor, string>();
	actorTreeInt = new BSTree<Actor, int>();
	actorTreeBool = new BSTree<Actor, bool>();
	movieTree = new BSTree<Movie, string>();
	movieTreeInt = new BSTree<Movie, int>();
	movieTreeDouble = new BSTree<Movie, double>();
}

void Menu::runMenu() { // Main driver of the program.
	std::ofstream outfile("output.csv"); // We open this now so we can pass the stream into the two write functions
	bool keepGoing = true;
	while (keepGoing) { //This while loop will only end if the user presses the close function (10)
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
		std::cout << "10. Quit the program." << std::endl;
		std::cout << "11. Write movie tree to file." << std::endl;
		std::cout << "12. Sort movie tree." << std::endl;
		std::cout << "13. Search movie tree." << std::endl;

		std::cin >> option;

		//If the input happens to not be a number, clear it and ask for the correct one again.
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(999, '\n');
			std::cout << "Please make sure you enter a number." << std::endl;
			std::cin >> option;
		}

		//Switch the selected input to run all the various functions
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
			//Firstly write the first line of the csv which shows the data types.
			outfile << "name,year,nominations,rating,duration,genre1,genre2,release,metacritic,synopsis" << std::endl;
			//Then pick the tree and write all the data from it in order.
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
		case 12:
			sortTreeMovie();
			break;
		case 13:
			searchMovie();
			break;
		}
	}
}

void Menu::readActors() {
	std::ifstream infile("actor-actress.csv");
	//Skip first line of file
	std::string junk, line;
	getline(infile, junk);

	while (getline(infile, line)) { //While we can still read lines
		std::stringstream ss(line); //Insert the line into a stream
		std::string name, award, film, yearS, winnerS; //we need to convert the last two to int and bool

		//Split up all the data by commas.
		getline(ss, yearS, ',');
		getline(ss, award, ',');
		getline(ss, winnerS, ',');
		getline(ss, name, ',');
		getline(ss, film, ',');

		int year;
		bool winner;
		//Convert the winner string into a bool based on if it's a 1 or 0.
		if (winnerS == "1") {
			winner = true;
		}
		else {
			winner = false;
		}

		//Convert the year string itno an integer
		year = stoi(yearS);

		Actor tempActor(year, name, award, film, winner);

		//Firstly add the new actor to the vector of data
		actorData.push_back(tempActor);
		//And then add it to the tree.
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
	//Skips first line
	std::string junk, line;
	getline(infile, junk);

	while (getline(infile, line)) { //While there are still lines to read
		std::stringstream ss(line);
		std::string name, genre1, genre2, release, synopsis, yearS, nominationsS, durationS, metacriticS, ratingS;
		int year, nominations, duration, metacritic;
		double rating;

		//Data is all read into a string stream and then split up by commas.
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

		//Substring skips the first space in the data file
		name = name.substr(1, name.size());

		year = stoi(yearS);
		//This is needed because sometimes nominations is filled in with "-", not an int
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
		//Converts rating to a double
		rating = stod(ratingS);

		Movie tempMovie(name, genre1, genre2, release, synopsis, year, nominations, duration, metacritic, rating);

		//Adds the new movie to the vector of data
		movieData.push_back(tempMovie);
		//sorry this is ugly :<
		//Picks the current tree and adds the newly created movie
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
	//Picks the tree and then calls the print in order function
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
	if((cTm == movName) || (cTm == movGenre1) || (cTm == movGenre2) || (cTm == movRelease) || (cTm == movSynopsis)) {
		movieTree->printInorder();
	}
	else if ((cTm == movYear) || (cTm == movNominations) || (cTm == movDuration) || (cTm == movMetacritic)) {
		movieTreeInt->printInorder();
	}
	else {
		movieTreeDouble->printInorder();
	}
}

void Menu::addRecordActors() {
	//This first part asks the user for all the data about the new actor they wish to add.
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

	//Converts the winner int into a boolean based on if it's 1 or 0
	if (winnerI == 1)
		winner = true;
	else if (winnerI == 0)
		winner = false;

	//Creates new actor
	Actor newActor(year, name, award, film, winner);

	//Adds new actor to main vector of data
	actorData.push_back(newActor);
	//Picks the current tree and adds new actor to it
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

void Menu::addRecordMovies() { // Identical to actor add, just instead collects data about a movie.
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

bool Menu::searchActor() { 
	//std::cin.ignore();
	int fieldChoice = 0;
	std::cout << "Which field would you like to search? (type the number)" << std::endl;
	std::cout << "1. Name" << std::endl;
	std::cout << "2. Award" << std::endl;
	std::cout << "3. Film" << std::endl;
	std::cout << "4. Year" << std::endl;


	std::cin >> fieldChoice;

	//Correct input guard
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(999, '\n');
		std::cout << "Please make sure you enter a number." << std::endl;
		std::cin >> fieldChoice;
	}

	if (fieldChoice != 4) { //Can't partial search on a year
		std::cout << "Would you like to perform a partial or exact search? (type exact or partial)" << std::endl;
		//presumeably if the user doesn't want to do anything they can just type something else.
		std::string searchChoice;
		std::cin.ignore();
		getline(std::cin, searchChoice);
		if (searchChoice == "partial") {
			partialSearchActor(fieldChoice);
		}
		else if (searchChoice == "exact") {
			exactSearchActor(fieldChoice);
		}
	}
	else {
		exactSearchActor(fieldChoice);
	}

	//std::cout << "What would you like to search for?" << std::endl;
	return true;
}

bool Menu::searchMovie() {
	//user will be able to type the number of the field they watn to search
	int fieldChoice = 0;
	std::cout << "Which field would you like to search? (type the number)" << std::endl;
	std::cout << "1. Name" << std::endl;
	std::cout << "2. Year" << std::endl;
	std::cout << "3. Nominations" << std::endl;
	std::cout << "4. Rating" << std::endl;
	std::cout << "5. Duration" << std::endl;
	std::cout << "6. Genre 1" << std::endl;
	std::cout << "7. Genre 2" << std::endl;
	std::cout << "8. Release" << std::endl;
	std::cout << "9. Metacritic Score" << std::endl;
	std::cout << "10. Synopsis" << std::endl;

	std::cin >> fieldChoice;

	//Correct input guard
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(999, '\n');
		std::cout << "Please make sure you enter a number." << std::endl;
		std::cin >> fieldChoice;
	}

	if (fieldChoice == 1 || fieldChoice == 6 || fieldChoice == 7 || fieldChoice == 8 || fieldChoice == 10) { //Can't partial search on any integer fields
		std::cout << "Would you like to perform a partial or exact search? (type exact or partial)" << std::endl;
		//presumeably if the user doesn't want to do anything they can just type something else.
		std::string searchChoice;
		std::cin.ignore();
		getline(std::cin, searchChoice);
		if (searchChoice == "partial") {
			partialSearchMovie(fieldChoice);
		}
		else if (searchChoice == "exact") {
			exactSearchMovie(fieldChoice);
		}
	}
	else {
		exactSearchMovie(fieldChoice);
	}

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

	//Correct input guard
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(999, '\n');
		std::cout << "Please make sure you enter a number." << std::endl;
		std::cin >> selection;
	}

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

void Menu::exactSearchActor(int choice) { //Searches are exact, based on if the search exactly matches the parameter
	std::string searchString;
	//bool keepSearching = false;
	int searchYear;
	std::string modDelChoice;
	//std::cin.ignore();
	switch (choice) { //Switches the parameter of the search
		case 1: //Name
			std::cout << "Please enter the name you'd like to perform an exact search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getName() == searchString) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		case 2: // Search award
			std::cout << "Please enter the award you'd like to perform an exact search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getAward() == searchString) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		case 3:
			std::cout << "Please enter the film you'd like to perform an exact search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getFilm() == searchString) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		case 4:
			std::cout << "Please enter the year you'd like to perform an exact search on." << std::endl;
			std::cin >> searchYear;
			std::cin.ignore();
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getYear() == searchYear) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		default:
			break;
	}
}

void Menu::exactSearchMovie(int choice) { //Searches are exact, based on if the search exactly matches the parameter
	std::string searchString;
	//bool keepSearching = false;
	int searchYear;
	std::string modDelChoice;
	double searchRating;
	//std::cin.ignore();
	switch (choice) { //Switches the parameter of the search
	case 1: //Name
		std::cout << "Please enter the name you'd like to perform an exact search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getName() == searchString) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 2: //Year
		std::cout << "Please enter the year you'd like to perform an exact search on." << std::endl;
		std::cin >> searchYear;
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getYear() == searchYear) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 3: //Nominations
		std::cout << "Please enter the nomination you'd like to perform an exact search on." << std::endl;
		std::cin >> searchYear;
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getNominations() == searchYear) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 4: //Rating
		std::cout << "Please enter the rating you'd like to perform an exact search on." << std::endl;
		std::cin >> searchRating;
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getRating() == searchRating) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 5: //Duration
		std::cout << "Please enter the duration you'd like to perform an exact search on." << std::endl;
		std::cin >> searchYear;
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getDuration() == searchYear) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 6: //Genre1
		std::cout << "Please enter the genre1 you'd like to perform an exact search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getGenre1() == searchString) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 7: //Genre2
		std::cout << "Please enter the genre2 you'd like to perform an exact search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getGenre2() == searchString) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 8: // Release
		std::cout << "Please enter the release month you'd like to perform an exact search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getRelease() == searchString) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 9: //Metacritic
		std::cout << "Please enter the metacritic you'd like to perform an exact search on." << std::endl;
		std::cin >> searchYear;
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getMetacritic() == searchYear) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 10: //Synopsis
		std::cout << "Please enter the release month you'd like to perform an exact search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getSynopsis() == searchString) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
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
}

void Menu::modifyRecordMovie(Movie &m) {
	//Delete the current node from the tree so we can reinsert the edited one.
	if (cTm == movName)
		movieTree->deleteNode(m.getName());
	else if (cTm == movGenre1)
		movieTree->deleteNode(m.getGenre1());
	else if (cTm == movGenre2)
		movieTree->deleteNode(m.getGenre2());
	else if (cTm == movRelease)
		movieTree->deleteNode(m.getRelease());
	else if (cTm == movSynopsis)
		movieTree->deleteNode(m.getSynopsis());
	else if (cTm == movYear)
		movieTreeInt->deleteNode(m.getYear());
	else if (cTm == movNominations)
		movieTreeInt->deleteNode(m.getNominations());
	else if (cTm == movDuration)
		movieTreeInt->deleteNode(m.getDuration());
	else if (cTm == movMetacritic)
		movieTreeInt->deleteNode(m.getMetacritic());
	else if (cTm == movRating)
		movieTreeDouble->deleteNode(m.getRating());

	//Ask user if they want to change any of the parameters
	//If they say yes, read in the info and edit that parameter
	//Do this for each parameter.
	std::string choice;
	int modifierI;
	double modifierD;
	std::string modifier;
	std::cout << "Would you like to change the name of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		m.setName(modifier);
	}
	std::cout << "Would you like to change the year of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		std::cin >> modifierI;
		m.setYear(modifierI);
	}
	std::cout << "Would you like to change the genre1 of the movie?" << std::endl;
	std::cin.ignore();
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		m.setGenre1(modifier);
	}
	std::cout << "Would you like to change the genre2 of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		m.setGenre2(modifier);
	}
	std::cout << "Would you like to change the release of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		m.setRelease(modifier);
	}
	std::cout << "Would you like to change the synopsis of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		getline(std::cin, modifier);
		m.setSynopsis(modifier);
	}
	std::cout << "Would you like to change the nominations of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		std::cin >> modifierI;
		m.setNominations(modifierI);
	}
	std::cout << "Would you like to change the duration of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		std::cin >> modifierI;
		m.setDuration(modifierI);
	}
	std::cout << "Would you like to change the metacritic of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		std::cin >> modifierI;
		m.setMetacritic(modifierI);
	}
	std::cout << "Would you like to change the rating of the movie?" << std::endl;
	getline(std::cin, choice);
	if (choice == "yes") {
		std::cout << "Change it to what?" << std::endl;
		std::cin >> modifierD;
		m.setRating(modifierD);
	}

	//Re-add the changed data to the tree
	if (cTm == movName)
		movieTree->addNode(m.getName(), m);
	else if (cTm == movGenre1)
		movieTree->addNode(m.getGenre1(), m);
	else if (cTm == movGenre2)
		movieTree->addNode(m.getGenre2(), m);
	else if (cTm == movRelease)
		movieTree->addNode(m.getRelease(), m);
	else if (cTm == movSynopsis)
		movieTree->addNode(m.getSynopsis(), m);
	else if (cTm == movYear)
		movieTreeInt->addNode(m.getYear(), m);
	else if (cTm == movNominations)
		movieTreeInt->addNode(m.getNominations(), m);
	else if (cTm == movDuration)
		movieTreeInt->addNode(m.getDuration(), m);
	else if (cTm == movMetacritic)
		movieTreeInt->addNode(m.getMetacritic(), m);
	else if (cTm == movRating)
		movieTreeDouble->addNode(m.getRating(), m);

}

void Menu::deleteRecordActor(Actor a) { //Picks the tree and removes the actor data from the list
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
}

void Menu::deleteRecordMovie(Movie m) { //Picks the tree currently in use and deletes the specified node
	if (cTm == movName)
		movieTree->deleteNode(m.getName());
	else if (cTm == movGenre1)
		movieTree->deleteNode(m.getGenre1());
	else if (cTm == movGenre2)
		movieTree->deleteNode(m.getGenre2());
	else if (cTm == movRelease)
		movieTree->deleteNode(m.getRelease());
	else if (cTm == movSynopsis)
		movieTree->deleteNode(m.getSynopsis());
	else if (cTm == movYear)
		movieTreeInt->deleteNode(m.getYear());
	else if (cTm == movNominations)
		movieTreeInt->deleteNode(m.getNominations());
	else if (cTm == movDuration)
		movieTreeInt->deleteNode(m.getDuration());
	else if (cTm == movMetacritic)
		movieTreeInt->deleteNode(m.getMetacritic());
	else if (cTm == movRating)
		movieTreeDouble->deleteNode(m.getRating());
}

void Menu::partialSearchActor(int choice) { // Limiting this to purely string values for now
	//Just a note, all these cases are identical aside from the fact that they search different parameters
	std::string searchString;
	int searchYear;
	bool continueSearching = true;
	std::string modDelChoice;
	//std::cin.ignore();
	switch (choice) {
		case 1: //Name
			std::cout << "Please enter the name you'd like to perform a partial search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getName().find(searchString) != std::string::npos) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

				std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes") {
					while (continueSearching) { //While the user wants to keep refining their search
						//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
						std::vector<Actor> refinedSearch = tempSortActorData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
						tempSortActorData.clear();

						continueSearching = false;
						std::cout << "Please enter the name you'd like to perform a partial search on." << std::endl;
						getline(std::cin, searchString);
						for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
							if (refinedSearch[i].getName().find(searchString) != std::string::npos) { //Check if any of the fields match the name
								refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
								tempSortActorData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
							}
						}
						if (tempSortActorData.size() != 0) { // If it actually found anything from that search
							std::cout << "Found these records:" << std::endl;
							for (int j = 0; j < tempSortActorData.size(); j++) {
								std::cout << tempSortActorData[j];
							}
							std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
							getline(std::cin, modDelChoice);
							if (modDelChoice == "yes")
								editDeleteRecords();

							std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
							getline(std::cin, modDelChoice);
							if (modDelChoice == "yes") { //Flag which will let the searching continue
								continueSearching = true;
							}

						}
						else { // Unsuccessful search
							std::cout << "Couldn't find any records based on that search parameter." << std::endl;
						}
					}
				}

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		case 2: // Search award
			std::cout << "Please enter the award you'd like to perform a partial search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getAward().find(searchString) != std::string::npos) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

				std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes") {
					while (continueSearching) { //While the user wants to keep refining their search
												//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
						std::vector<Actor> refinedSearch = tempSortActorData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
						tempSortActorData.clear();

						continueSearching = false;
						std::cout << "Please enter the award you'd like to perform a partial search on." << std::endl;
						getline(std::cin, searchString);
						for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
							if (refinedSearch[i].getAward().find(searchString) != std::string::npos) { //Check if any of the fields match the name
								refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
								tempSortActorData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
							}
						}
						if (tempSortActorData.size() != 0) { // If it actually found anything from that search
							std::cout << "Found these records:" << std::endl;
							for (int j = 0; j < tempSortActorData.size(); j++) {
								std::cout << tempSortActorData[j];
							}
							std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
							getline(std::cin, modDelChoice);
							if (modDelChoice == "yes")
								editDeleteRecords();

							std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
							getline(std::cin, modDelChoice);
							if (modDelChoice == "yes") { //Flag which will let the searching continue
								continueSearching = true;
							}

						}
						else { // Unsuccessful search
							std::cout << "Couldn't find any records based on that search parameter." << std::endl;
						}
					}
				}

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		case 3:
			std::cout << "Please enter the film you'd like to perform a partial search on." << std::endl;
			getline(std::cin, searchString);
			for (int i = 0; i < actorData.size(); i++) { // Loop through the actorDatabase vector
				if (actorData[i].getFilm().find(searchString) != std::string::npos) { //Check if any of the fields match the name
					actorData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
					tempSortActorData.push_back(actorData[i]); // Add the data to a temporary vector in case we want to re-search the data.
				}
			}
			if (tempSortActorData.size() != 0) { // If it actually found anything from that search
				std::cout << "Found these records:" << std::endl;
				for (int j = 0; j < tempSortActorData.size(); j++) {
					std::cout << tempSortActorData[j];
				}
				std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes")
					editDeleteRecords();

				std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
				getline(std::cin, modDelChoice);
				if (modDelChoice == "yes") {
					while (continueSearching) { //While the user wants to keep refining their search
												//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
						std::vector<Actor> refinedSearch = tempSortActorData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
						tempSortActorData.clear();

						continueSearching = false;
						std::cout << "Please enter the film you'd like to perform a partial search on." << std::endl;
						getline(std::cin, searchString);
						for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
							if (refinedSearch[i].getFilm().find(searchString) != std::string::npos) { //Check if any of the fields match the name
								refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
								tempSortActorData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
							}
						}
						if (tempSortActorData.size() != 0) { // If it actually found anything from that search
							std::cout << "Found these records:" << std::endl;
							for (int j = 0; j < tempSortActorData.size(); j++) {
								std::cout << tempSortActorData[j];
							}
							std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
							getline(std::cin, modDelChoice);
							if (modDelChoice == "yes")
								editDeleteRecords();

							std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
							getline(std::cin, modDelChoice);
							if (modDelChoice == "yes") { //Flag which will let the searching continue
								continueSearching = true;
							}

						}
						else { // Unsuccessful search
							std::cout << "Couldn't find any records based on that search parameter." << std::endl;
						}
					}
				}

			}
			else { // Unsuccessful search
				std::cout << "Couldn't find any records based on that search parameter." << std::endl;
			}
			tempSortActorData.clear(); //Empty the vector once we're done with it.
			break;
		default:
			break;
	}
}

void Menu::partialSearchMovie(int choice) {
	std::string searchString;
	bool continueSearching = true;
	std::string modDelChoice;
	//std::cin.ignore();
	switch (choice) {
	case 1: //Name
		std::cout << "Please enter the name you'd like to perform a partial search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getName().find(searchString) != std::string::npos) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

			std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes") {
				while (continueSearching) { //While the user wants to keep refining their search
											//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
					std::vector<Movie> refinedSearch = tempSortMovieData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
					tempSortMovieData.clear();

					continueSearching = false;
					std::cout << "Please enter the name you'd like to perform a partial search on." << std::endl;
					getline(std::cin, searchString);
					for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
						if (refinedSearch[i].getName().find(searchString) != std::string::npos) { //Check if any of the fields match the name
							refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
							tempSortMovieData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
						}
					}
					if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
						std::cout << "Found these records:" << std::endl;
						for (int j = 0; j < tempSortMovieData.size(); j++) {
							std::cout << tempSortMovieData[j];
						}
						std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes")
							editDeleteRecordsMovie();

						std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes") { //Flag which will let the searching continue
							continueSearching = true;
						}

					}
					else { // Unsuccessful search
						std::cout << "Couldn't find any records based on that search parameter." << std::endl;
					}
				}
			}

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 6: //Genre 1
		std::cout << "Please enter the genre1 you'd like to perform a partial search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getGenre1().find(searchString) != std::string::npos) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

			std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes") {
				while (continueSearching) { //While the user wants to keep refining their search
											//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
					std::vector<Movie> refinedSearch = tempSortMovieData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
					tempSortMovieData.clear();

					continueSearching = false;
					std::cout << "Please enter the genre1 you'd like to perform a partial search on." << std::endl;
					getline(std::cin, searchString);
					for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
						if (refinedSearch[i].getGenre1().find(searchString) != std::string::npos) { //Check if any of the fields match the name
							refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
							tempSortMovieData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
						}
					}
					if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
						std::cout << "Found these records:" << std::endl;
						for (int j = 0; j < tempSortMovieData.size(); j++) {
							std::cout << tempSortMovieData[j];
						}
						std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes")
							editDeleteRecordsMovie();

						std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes") { //Flag which will let the searching continue
							continueSearching = true;
						}

					}
					else { // Unsuccessful search
						std::cout << "Couldn't find any records based on that search parameter." << std::endl;
					}
				}
			}

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 7: //Genre 2
		std::cout << "Please enter the genre2 you'd like to perform a partial search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getGenre2().find(searchString) != std::string::npos) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

			std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes") {
				while (continueSearching) { //While the user wants to keep refining their search
											//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
					std::vector<Movie> refinedSearch = tempSortMovieData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
					tempSortMovieData.clear();

					continueSearching = false;
					std::cout << "Please enter the genre2 you'd like to perform a partial search on." << std::endl;
					getline(std::cin, searchString);
					for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
						if (refinedSearch[i].getGenre2().find(searchString) != std::string::npos) { //Check if any of the fields match the name
							refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
							tempSortMovieData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
						}
					}
					if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
						std::cout << "Found these records:" << std::endl;
						for (int j = 0; j < tempSortMovieData.size(); j++) {
							std::cout << tempSortMovieData[j];
						}
						std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes")
							editDeleteRecordsMovie();

						std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes") { //Flag which will let the searching continue
							continueSearching = true;
						}

					}
					else { // Unsuccessful search
						std::cout << "Couldn't find any records based on that search parameter." << std::endl;
					}
				}
			}

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 8:
		std::cout << "Please enter the release month you'd like to perform a partial search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getRelease().find(searchString) != std::string::npos) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

			std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes") {
				while (continueSearching) { //While the user wants to keep refining their search
											//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
					std::vector<Movie> refinedSearch = tempSortMovieData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
					tempSortMovieData.clear();

					continueSearching = false;
					std::cout << "Please enter the release month you'd like to perform a partial search on." << std::endl;
					getline(std::cin, searchString);
					for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
						if (refinedSearch[i].getRelease().find(searchString) != std::string::npos) { //Check if any of the fields match the name
							refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
							tempSortMovieData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
						}
					}
					if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
						std::cout << "Found these records:" << std::endl;
						for (int j = 0; j < tempSortMovieData.size(); j++) {
							std::cout << tempSortMovieData[j];
						}
						std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes")
							editDeleteRecordsMovie();

						std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes") { //Flag which will let the searching continue
							continueSearching = true;
						}

					}
					else { // Unsuccessful search
						std::cout << "Couldn't find any records based on that search parameter." << std::endl;
					}
				}
			}

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	case 10:
		std::cout << "Please enter the synopsis you'd like to perform a partial search on." << std::endl;
		getline(std::cin, searchString);
		for (int i = 0; i < movieData.size(); i++) { // Loop through the movieDatabase vector
			if (movieData[i].getSynopsis().find(searchString) != std::string::npos) { //Check if any of the fields match the name
				movieData[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
				tempSortMovieData.push_back(movieData[i]); // Add the data to a temporary vector in case we want to re-search the data.
			}
		}
		if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
			std::cout << "Found these records:" << std::endl;
			for (int j = 0; j < tempSortMovieData.size(); j++) {
				std::cout << tempSortMovieData[j];
			}
			std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes")
				editDeleteRecordsMovie();

			std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
			getline(std::cin, modDelChoice);
			if (modDelChoice == "yes") {
				while (continueSearching) { //While the user wants to keep refining their search
											//This loop is exactly the same as the before code, except now it acts on the smaller refined data from the search
					std::vector<Movie> refinedSearch = tempSortMovieData; //Here we just store the previous search into another vector and then clear it so we stick the new search results into it
					tempSortMovieData.clear();

					continueSearching = false;
					std::cout << "Please enter the synopsis you'd like to perform a partial search on." << std::endl;
					getline(std::cin, searchString);
					for (int i = 0; i < refinedSearch.size(); i++) { // Loop through the new refined search vector
						if (refinedSearch[i].getSynopsis().find(searchString) != std::string::npos) { //Check if any of the fields match the name
							refinedSearch[i].setTempPos(i); // Set the position of the data in the main vector so we can delete it in our delete function.
							tempSortMovieData.push_back(refinedSearch[i]); // Add the data to a temporary vector in case we want to re-search the data.
						}
					}
					if (tempSortMovieData.size() != 0) { // If it actually found anything from that search
						std::cout << "Found these records:" << std::endl;
						for (int j = 0; j < tempSortMovieData.size(); j++) {
							std::cout << tempSortMovieData[j];
						}
						std::cout << "Would you like to edit or modify them? (type yes if so)" << std::endl; // If the user wants to edit their search result as well.
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes")
							editDeleteRecordsMovie();

						std::cout << "Would you like to refine your search? (type yes if so)" << std::endl;
						getline(std::cin, modDelChoice);
						if (modDelChoice == "yes") { //Flag which will let the searching continue
							continueSearching = true;
						}

					}
					else { // Unsuccessful search
						std::cout << "Couldn't find any records based on that search parameter." << std::endl;
					}
				}
			}

		}
		else { // Unsuccessful search
			std::cout << "Couldn't find any records based on that search parameter." << std::endl;
		}
		tempSortMovieData.clear(); //Empty the vector once we're done with it.
		break;
	default:
		break;
	}
}

void Menu::editDeleteRecords() { 
	std::string modDelChoice, quitChoice;
	for (int i = 0; i < tempSortActorData.size(); i++) {
		//Loops through all the records that the user found in their last search
		std::cout << "Found this record: " << std::endl;
		std::cout << tempSortActorData[i];
		std::cout << "Would you like to delete or modify this record? (type modify or delete)" << std::endl;
		//They get given the optoin to modify or delete each one based on what they choose
		getline(std::cin, modDelChoice);
		if (modDelChoice == "modify") {
			modifyRecordActor(tempSortActorData[i]);
		}
		else if (modDelChoice == "delete") {
			actorData.erase(actorData.begin() + tempSortActorData[i].getTempPos()); //Firstly erase it from the main vector that stores all the data
			deleteRecordActor(tempSortActorData[i]); //Lastly delete it from the tree that's currently being used
		}

		//If they don't want to keep going through the list, they can stop at any time
		std::cout << "Would you like to continue editing records? (type yes if so)" << std::endl;
		getline(std::cin, quitChoice);
		if (quitChoice != "yes") {
			break;
		}
	}
}

void Menu::editDeleteRecordsMovie() {
	std::string modDelChoice, quitChoice;
	for (int i = 0; i < tempSortMovieData.size(); i++) {
		//Loops through all the records that the user found in their last search
		std::cout << "Found this record: " << std::endl;
		std::cout << tempSortMovieData[i];
		std::cout << "Would you like to delete or modify this record? (type modify or delete)" << std::endl;
		//They get given the optoin to modify or delete each one based on what they choose
		getline(std::cin, modDelChoice);
		if (modDelChoice == "modify") {
			modifyRecordMovie(tempSortMovieData[i]);
		}
		else if (modDelChoice == "delete") {
			movieData.erase(movieData.begin() + tempSortMovieData[i].getTempPos()); //Firstly erase it from the main vector that stores all the data
			deleteRecordMovie(tempSortMovieData[i]); //Lastly delete it from the tree that's currently being used
		}

		//If they don't want to keep going through the list, they can stop at any time
		std::cout << "Would you like to continue editing records? (type yes if so)" << std::endl;
		getline(std::cin, quitChoice);
		if (quitChoice != "yes") {
			break;
		}
	}
}

void Menu::sortTreeMovie() {
	//Ask for which key the user would like to sort the tree by.
	std::cout << "Which parameter would you like to sort the movie tree by?" << std::endl;
	std::cout << "1. Name" << std::endl;
	std::cout << "2. Year" << std::endl;
	std::cout << "3. Nominations" << std::endl;
	std::cout << "4. Rating" << std::endl;
	std::cout << "5. Duration" << std::endl;
	std::cout << "6. Genre 1" << std::endl;
	std::cout << "7. Genre 2" << std::endl;
	std::cout << "8. Release" << std::endl;
	std::cout << "9. Metacritic Score" << std::endl;
	std::cout << "10. Synopsis" << std::endl;

	int selection = 0;
	std::cin >> selection;

	//Correct input guard
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(999, '\n');
		std::cout << "Please make sure you enter a number." << std::endl;
		std::cin >> selection;
	}

	//Picks the paremeter
	//Deletes the current tree in use
	//Readds everything to the tree based on the new key.
	switch (selection) {
	case 1:
		deleteCurrentTreeMovie();
		cTm = movName;
		for (int i = 0; i < movieData.size(); i++) {
			movieTree->addNode(movieData[i].getName(), movieData[i]);
		}
		break;
	case 2:
		deleteCurrentTreeMovie();
		cTm = movYear;
		for (int i = 0; i < movieData.size(); i++) {
			movieTreeInt->addNode(movieData[i].getYear(), movieData[i]);
		}
		break;
	case 3:
		deleteCurrentTreeMovie();
		cTm = movNominations;
		for (int i = 0; i < movieData.size(); i++) {
			movieTreeInt->addNode(movieData[i].getNominations(), movieData[i]);
		}
		break;
	case 4:
		deleteCurrentTreeMovie();
		cTm = movRating;
		for (int i = 0; i < movieData.size(); i++) {
			movieTreeDouble->addNode(movieData[i].getRating(), movieData[i]);
		}
		break;
	case 5:
		deleteCurrentTreeMovie();
		cTm = movDuration;
		for (int i = 0; i < movieData.size(); i++) {
			movieTreeInt->addNode(movieData[i].getDuration(), movieData[i]);
		}
		break;
	case 6:
		deleteCurrentTreeMovie();
		cTm = movGenre1;
		for (int i = 0; i < movieData.size(); i++) {
			movieTree->addNode(movieData[i].getGenre1(), movieData[i]);
		}
		break;
	case 7:
		deleteCurrentTreeMovie();
		cTm = movGenre2;
		for (int i = 0; i < movieData.size(); i++) {
			movieTree->addNode(movieData[i].getGenre2(), movieData[i]);
		}
		break;
	case 8:
		deleteCurrentTreeMovie();
		cTm = movRelease;
		for (int i = 0; i < movieData.size(); i++) {
			movieTree->addNode(movieData[i].getRelease(), movieData[i]);
		}
		break;
	case 9:
		deleteCurrentTreeMovie();
		cTm = movMetacritic;
		for (int i = 0; i < movieData.size(); i++) {
			movieTreeInt->addNode(movieData[i].getMetacritic(), movieData[i]);
		}
		break;
	case 10:
		deleteCurrentTreeMovie();
		cTm = movSynopsis;
		for (int i = 0; i < movieData.size(); i++) {
			movieTree->addNode(movieData[i].getSynopsis(), movieData[i]);
		}
		break;
	default:
		break;
	}
}

void Menu::deleteCurrentTreeMovie() { //picks the current stored tree and deletes it
	if ((cTm == movName) || (cTm == movGenre1) || (cTm == movGenre2) || (cTm == movRelease) || (cTm == movSynopsis)) {
		delete movieTree;
		movieTree = new BSTree<Movie, string>();
	}
	else if ((cTm == movYear) || (cTm == movNominations) || (cTm == movDuration) || (cTm == movMetacritic)) {
		delete movieTreeInt;
		movieTreeInt = new BSTree<Movie, int>();
	}
	else {
		delete movieTreeDouble;
		movieTreeDouble = new BSTree<Movie, double>();
	}
}



