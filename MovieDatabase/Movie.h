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
	std::string getGenre1() { return genre1; }
	void setGenre1(std::string _genre1) { genre1 = _genre1; }
	std::string getGenre2() { return genre2; }
	void setGenre2(std::string _genre2) { genre2 = _genre2; }
	std::string getRelease() { return release; }
	void setRelease(std::string _release) { release = _release; }
	std::string getSynopsis() { return synopsis; }
	void setSynopsis(std::string _synopsis) { synopsis = _synopsis; }

	int getYear() { return year; }
	void setYear(int _year) { year = _year; }
	int getNominations() { return nominations; }
	void setNominations(int _nominations) { nominations = _nominations; }
	int getDuration() { return duration; }
	void setDuration(int _duration) { duration = _duration; }
	int getMetacritic() { return metacritic; }
	void setMetacritic(int _metacritic) { metacritic = _metacritic; }

	double getRating() { return rating; }
	void setRating(double _rating) { rating = _rating; }
	friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};

#endif