#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
	std::string name, genre1, genre2, release, synopsis;
	int year, nominations, duration, metacritic;
	double rating;
public:
	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }
};

#endif