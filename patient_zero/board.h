#ifndef BOARD_H
#define BOARD_H
#include "field.h"
#include <vector>

class board{
	//height and width are declared here but should be variable
	const static int WIDTH = 20;
	const static int HEIGHT = 20;
	std::vector<std::vector<field> > blocks;

public:
	//board(int, int);
	board();
	std::vector<std::vector<field> > getBlocks();
	int getHeight();
	int getWidth();
	void fillBoard();

};

#endif