#include <iostream>
//#include "BinarySearchTree.h"
#include "Actor.h"
#include "Menu.h"

int main()
{
	Menu mainMenu;
	mainMenu.readActors();
	mainMenu.readMovies();
	mainMenu.printInOrderMovies();

    return 0; 
}

