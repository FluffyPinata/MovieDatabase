#include "Actor.h"

//Created by Gabriel Jones

Actor::Actor() { //Default constructor
	year = 0;
	name = "";
	film = "";
	award = "";
	winner = false;
	tempPosition = -1;
}


//Contructor if you already know the data
Actor::Actor(int _year, std::string _name, std::string _award, std::string _film, bool _winner) {
	year = _year;
	name = _name;
	film = _film;
	award = _award;
	winner = _winner;
	tempPosition = -1;
}

//Overload prints exactly the same as format in file
std::ostream& operator<<(std::ostream& os, const Actor& a) {
	os << a.year << "," << a.award << "," << a.winner << "," << a.name << "," << a.film << std::endl;
	return os;
}