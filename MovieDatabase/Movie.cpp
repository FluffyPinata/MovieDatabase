#include "Movie.h"

//Created by Gabriel Jones

Movie::Movie() { //Default constructor
	name = "", genre1 = "", genre2 = "", release = "", synopsis = "";
	year = 0, nominations = 0, duration = 0, metacritic = 0;
	rating = 0.0;
	tempPos = -1;
}

//Constructor if you already know all the data
Movie::Movie(std::string _name, std::string _genre1, std::string _genre2, std::string _release, std::string _synopsis, int _year, int _nominations, int _duration, int _metacritic, double _rating) {
	name = _name;
	genre1 = _genre1;
	genre2 = _genre2;
	release = _release;
	synopsis = _synopsis;
	year = _year;
	nominations = _nominations;
	duration = _duration;
	metacritic = _metacritic;
	rating = _rating;
	tempPos = -1;
}

//Overload prints exactly the same as it was in the file
std::ostream& operator<<(std::ostream& os, const Movie& m) {
	os << m.name << "," << m.year << "," << m.nominations << "," << m.rating << "," << m.duration << "," << m.genre1 << "," << m.genre2 << "," << m.release << "," << m.metacritic << "," << m.synopsis << std::endl;
	return os;
}