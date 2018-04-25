#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
	std::string name, genre1, genre2, release, synopsis;
	int year, nominations, duration, metacritic;
	double rating;
public:
	Movie();
	Movie(std::string _name, std::string _genre1, std::string _genre2, std::string _release, std::string _synopsis, int _year, int _nominations, int _duration, int _metacritic, double _rating);
	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }
	friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};

#endif