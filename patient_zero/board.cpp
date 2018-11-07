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
	std::cout << "board basic constructor is called" << std::endl;
	//blocks = std::vector<std::vector<field> >(HEIGHT, std::vector<field>(WIDTH));
	field* block1 = new field(1);
	std::cout << "block id " << (*(block1)).id << std::endl;
	std::cout << "Haaalo1" << std::endl;
	blocks.at(0).at(0) = *block1;
	std::cout << "Haaalo" << std::endl;
	std::cout << "block id " << blocks.at(0).at(0).id << std::endl;
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
