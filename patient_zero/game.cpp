#include <iostream>
#include <vector>
#include <stdlib.h>
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
	fillBoard();
	for(int i = 0; i < Number_Persons; i++){
		std::cout << "y: " << persons.at(i).getPosY() << ", x: " << persons.at(i).getPosX() << std::endl;
	}
	moveAndInfect();
	std::cout << "Number of infected: " << numberOfInfected() << std::endl << "Number of healthy: " << (Number_Persons - numberOfInfected()) << std::endl;
}

void game::fillBoard(){
	int randX;
	int randY;

	randX = randomInt(0, playground.getWidth());
	randY = randomInt(0, playground.getHeight());

	for(int i = 0; i < Number_Persons; i++){ //for every person in persons
		while(playground.getBlocks().at(randY).at(randX).getHasPerson() == true){ //while the field (randX, randY) is already owned, create new randX and randY
			randX = randomInt(0, playground.getWidth());
			randY = randomInt(0, playground.getHeight());
			std::cout << "y: " << randY << ", x: " << randX << std::endl;
		}
		
		std::cout << "y: " << randY << ", x: " << randX << std::endl;

		playground.getBlocks().at(randY).at(randX).setOwner(persons.at(i));
		playground.getBlocks().at(randY).at(randX).setHasPerson(true);
		playground.getBlocks().at(randY).at(randX).getOwner().setPosX(randX);
		playground.getBlocks().at(randY).at(randX).getOwner().setPosY(randY);
	}
}

int game::randomInt(int min, int max){
	int r = rand()%(max - min) + min; //random int between min and max 
	return r;
}

void game::moveAndInfect(){
	int direction;

	for(int i = 0; i < Number_Persons; i++){
		//player moving
		//direction = randomInt(1, 4);
		direction = 2;
		std::cout << "direction: " << direction << std::endl;
		switch(direction){
			case 1:
				if(persons.at(i).getPosY() - 1 >= 0){
					movePersons(0, -1, i);
				}
				break;
			case 2:
				if(persons.at(i).getPosX() - 1 >= 0){
					std::cout << "entered switch case correctly" << std::endl;
					movePersons(-1, 0, i);
				}
				break;
			case 3:
				if(persons.at(i).getPosY() + 1 < playground.getHeight()){
					movePersons(0, 1, i);
				}
				break;
			case 4:
				if(persons.at(i).getPosX() + 1 < playground.getWidth()){
					movePersons(1, 0, i);
				}
				break;
		}
		std::cout << "left switch case correctly" << std::endl;

		//player infecting
		if(persons.at(i).getPosY() - 1 >= 0){ 
			castInfection(0, -1, i);
		}
		if(persons.at(i).getPosX() - 1 >= 0){ 
			castInfection(-1, 0, i);
		}
		if(persons.at(i).getPosY() + 1 < playground.getHeight()){ 
			castInfection(0, 1, i);
		}
		if(persons.at(i).getPosX() + 1 < playground.getWidth()){ 
			castInfection(1, 0, i);
		}

		//player healing
		if(persons.at(i).getPosY() - 1 >= 0){ 
			castHealing(0, -1, i);
		}
		else if(persons.at(i).getPosX() - 1 >= 0){ 
			castHealing(-1, 0, i);
		}
		else if(persons.at(i).getPosY() + 1 < playground.getHeight()){ 
			castHealing(0, 1, i);
		}
		else if(persons.at(i).getPosX() + 1 < playground.getWidth()){ 
			castHealing(1, 0, i);
		}
	}
}

void game::changePersonInfected(int dx, int dy, int i){ //change the infected state of the person
	bool status = playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getOwner().getInfected(); 
	playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getOwner().setInfected(!status); //switch the infected state
}

void game::castInfection(int dx, int dy, int i){
	if(!checkForInfectedNeighbour(dx, dy, i)){ //check if the neighbour is already infected
		if(abilitySuccessful(playground.getBlocks().at(persons.at(i).getPosY()).at(persons.at(i).getPosX()).getOwner().getInfectious(), i)){ //check if person will use its ability
			changePersonInfected(dx, dy, i);
		}
	}
}

void game::castHealing(int dx, int dy, int i){
	if(checkForInfectedNeighbour(dx, dy, i)){ //check if the neighbour is already infected
		if(abilitySuccessful(playground.getBlocks().at(persons.at(i).getPosY()).at(persons.at(i).getPosX()).getOwner().getInfectious(), i)){ //check if person will use its ability
			changePersonInfected(dx, dy, i);
		}
	}
}

bool game::abilitySuccessful(float abilityValue, int i){
	float comparisonValue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if(abilityValue > comparisonValue){ //if abilityValue is bigger than the random 0.0 to 1.0 float, the ability is successful and will be used
		return true;
	}
	return false;
}

bool game::checkForInfectedNeighbour(int dx, int dy, int i){
	if(playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getHasPerson() == true){ //check if neighbour field has a Person on it
		if(playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getOwner().getInfected() == true){ //check if neighbour is infected
			return true;
		}
	}
	return false;
}

void game::movePersons(int dx, int dy, int i){
	std::cout << "dx: " << dx << " dy: " << dy << " i:  " << i << std::endl;
	std::cout << "Height: " << playground.getHeight() << std::endl;
	std::cout << "Width: " << playground.getWidth() << std::endl;
	std::cout << "person y: " << persons.at(i).getPosY() << "person x: " << persons.at(i).getPosX() << std::endl;
	std::cout << playground.getBlocks()[persons.at(i).getPosY() + dy][persons.at(i).getPosX() + dx].getHasPerson() << std::endl;
	if(playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getHasPerson() == false){
		playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).setOwner(persons.at(i)); //change owner of the new field
		playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).setHasPerson(true); //new field has now a owner
		playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getOwner().setPosX(persons.at(i).getPosX() + dx); //change x pos of person
		playground.getBlocks().at(persons.at(i).getPosY() + dy).at(persons.at(i).getPosX() + dx).getOwner().setPosY(persons.at(i).getPosY() + dy); //change y pos of person
		playground.getBlocks().at(persons.at(i).getPosY()).at(persons.at(i).getPosX()).setHasPerson(false); //old field has no owner anymore
	}
}

int game::numberOfInfected(){
	int counter = 0;

	for(int i = 0; i < Number_Persons; i++){
		if(persons.at(i).getInfected()){
			counter++;
		}
	}

	return counter;
}

int main(){
	srand (time(NULL));

	game g;
	g.play();
	return 0;
}
