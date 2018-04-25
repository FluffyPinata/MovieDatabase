#include "Movie.h"

Movie::Movie() {
	std::string name = "", genre1 = "", genre2 = "", release = "", synopsis = "";
	int year = 0, nominations = 0, duration = 0, metacritic = 0;
	double rating = 0.0;
}

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
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
	os << "---------" << std::endl;
	os << "Name: " << m.name << std::endl;
	os << "Genres: " << m.genre1 << " " << m.genre2 << std::endl;
	os << "Release: " << m.year << " " << m.release << std::endl;
	os << "Nominations: " << m.nominations << std::endl;
	os << "Duration: " << m.duration << std::endl;
	os << "Metacritic score: " << m.metacritic << std::endl;
	os << "Rating: " << m.rating << std::endl;
	os << "Synopsis: " << m.synopsis << std::endl;
	return os;
}