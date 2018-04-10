#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>

class Actor {
private:
	int year;
	std::string award, name, film;
	bool winner;
public:
	Actor();
	Actor(int _year, std::string _name, std::string _award, std::string _film, bool _winner);
};

#endif