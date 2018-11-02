#include <iostream>
#include <vector>
#include "game.h"
#include "infection.h"
#include "person.h"
#include "field.h"
#include "board.h"

game::game(){
	persons = std::vector<person>(Number_Persons);
}

board game::getBoard(){
	return playground;
}

std::vector<person> game::getPersons(){
	return persons;
}

void game::play(){
	playground.fillBoard(Number_Persons, persons);
	moveAndInfect();
}

void game::moveAndInfect(){
	
}

int main(){
	game g;
	g.play();
	return 0;
}
