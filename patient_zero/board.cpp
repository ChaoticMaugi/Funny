#include "board.h"
#include <iostream>
#include <vector>
#include "field.h"

/*
board::board(int h, int w){
	HEIGHT = h;
	WIDTH = w;
	blocks = new field[HEIGHT][WIDTH];
}
*/

board::board(){
	blocks = std::vector<std::vector<field> >(HEIGHT, std::vector<field>(WIDTH));
}

std::vector<std::vector<field> > board::getBlocks(){
	return blocks;
}

int board::getHeight(){
	return HEIGHT;
}

int board::getWidth(){
	return WIDTH;
}

void board::fillBoard(int Number_Persons, std::vector<person> persons){
	int randX;
	int randY;

	randX = randomInt(0, HEIGHT);
	randY = randomInt(0, WIDTH);

	for(int i = 0; i < Number_Persons; i++){ //for every person in persons
		while(blocks.at(randX).at(randY).getHasPerson() == true){ //while the field (randX, randY) is already owned, create new randX and randY
			randX = randomInt(0, HEIGHT);
			randY = randomInt(0, WIDTH);
		}

		blocks.at(randX).at(randY).setOwner(persons.at(i));
		blocks.at(randX).at(randY).setHasPerson(true);
		blocks.at(randX).at(randY).getOwner().setPosX(randX);
		blocks.at(randX).at(randY).getOwner().setPosX(randY);
	}
}

int board::randomInt(int min, int max){
	int r = (max - min)*rand() + min; //random int between min and max 
	return r;
}

/*
int main() {
	board b;
	
	for(int h = 0; h < b.getHeight(); h++){
		for(int w = 0; w < b.getWidth(); w++){
			std::cout << b.getBlocks().at(h).at(w).getHasPerson() << std::endl;
		}
	}
	
	return 0;
}
*/