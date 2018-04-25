#include "Actor.h"

Actor::Actor() {
	year = 0;
	name = "";
	film = "";
	award = "";
	winner = false;
}

Actor::Actor(int _year, std::string _name, std::string _award, std::string _film, bool _winner) {
	year = _year;
	name = _name;
	film = _film;
	award = _award;
	winner = _winner;
}

std::ostream& operator<<(std::ostream& os, const Actor& a) {
	os << "---------" << std::endl;
	os << "Name: " << a.name << std::endl;
	os << "Award: " << a.award << std::endl;
	os << "Film: " << a.film << std::endl;
	os << "Year: " << a.year << std::endl;
	os << "Winner?: " << a.winner << std::endl;
	return os;
}