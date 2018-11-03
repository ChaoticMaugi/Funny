#ifndef GAME_H
#define GAME_H
#include <vector>
#include "person.h"
#include "board.h"

class game{
	const static int Number_Persons = 10; //change for more or fewer persons
	std::vector<person> persons;
	board playground;

public:
	game();
	board getBoard();
	std::vector<person> getPersons();
	void play();
	void moveAndInfect();
	void movePersons(int, int, int);
	bool checkForInfectedNeighbour(int, int, int);
	bool abilitySuccessful(float, int);
	void castInfection(int, int, int);
	void castHealing(int, int, int);
	void changePersonInfected(int, int, int);
	int numberOfInfected();
	void fillBoard();
	int randomInt(int, int);

};

#endif