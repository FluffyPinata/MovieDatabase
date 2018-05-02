#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>

class Actor {
private:
	int year, tempPosition;
	std::string award, name, film;
	bool winner;
public:
	Actor();
	Actor(int _year, std::string _name, std::string _award, std::string _film, bool _winner);
	int getYear() { return year; }
	void setYear(int _year) { year = _year; }
	std::string getName() { return name; }
	void setName(std::string _name) { name = _name; }
	std::string getAward() { return award; }
	void setAward(std::string _award) { award = _award; }
	std::string getFilm() { return film; }
	void setFilm(std::string _film) { film = _film; }
	bool getWinner() { return winner; }
	void setWinner(bool _winner) { winner = _winner; }
	int getTempPos() { return tempPosition; }
	void setTempPos(int _tempPos) { tempPosition = _tempPos; }
	friend std::ostream& operator<<(std::ostream& os, const Actor& a);
};

#endif