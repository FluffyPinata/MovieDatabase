#include <iostream>
//#include "BinarySearchTree.h"
#include "Actor.h"
#include "Menu.h"

int main()
{
	Menu mainMenu;
	mainMenu.readActors();
	mainMenu.addRecordActors();
	mainMenu.printInOrderActors();

    return 0; 
}

