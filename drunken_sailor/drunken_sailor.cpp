#include <iostream>
#include <stdlib.h>

int randomNumber();

int main() {

	srand (time(NULL));

	int FIELD_HEIGTH = 12;
	int FIELD_WIDTH = 15;
	int field [12][15];
	int start_pos_x;
	int start_pos_y;
	int pos_x;
	int pos_y;
	int direction; //1 = up, 2 = left, 3 = down, 4 = right
	bool won = false;
	int counter;

	//Set field to 0 overall
	for(int i = 0; i < FIELD_HEIGTH; i++){
		for(int j = 0; j < FIELD_WIDTH; j++){
			field[i][j] = 0;
		}
	}

	//Set Exit point to 1
	field[0][4] = 1;
	field[0][10] = 1;
	field[4][0] = 1;
	field[4][14] = 1;
	field[7][0] = 1;
	field[7][14] = 1;
	field[11][4] = 1;
	field[11][10] = 1;

	//Set start position
	start_pos_x = 7;
	start_pos_y = 4;
	pos_x = start_pos_x;
	pos_y = start_pos_y;

	//monte carlo loop
	int monte = 100; //number of simulations
	for(int i = 0; i < monte; i++){

		//game loop
		won = false;
		counter = 0;
		pos_x = start_pos_x;
		pos_y = start_pos_y;

		while(!won) {
			counter++;
			direction = randomNumber();

			if(direction == 1){
				if(field[pos_x][pos_y-1] == 1){
					std::cout << "The sailor got home! With only " << counter << " moves." << std::endl;
					won = true;
				}
				else if((pos_y - 3) > 0){
				pos_y -= 3;
				}
			}
			else if(direction == 2){
				if(field[pos_x-1][pos_y] == 1){
					std::cout << "The sailor got home! With only " << counter << " moves." << std::endl;
					won = true;
				}
				else if((pos_x - 3) > 0){
					pos_x -= 3;
				}
			}
			else if(direction == 3){
				if(field[pos_x][pos_y+1] == 1){
					std::cout << "The sailor got home! With only " << counter << " moves." << std::endl;
					won = true;
				}
				else if((pos_y + 3) < FIELD_HEIGTH){
					pos_y += 3;
				}
			}
			else if (direction == 4)
			{
				 if(field[pos_x+1][pos_y] == 1){
					std::cout << "The sailor got home! With only " << counter << " moves." << std::endl;
					won = true;
				}
				else if((pos_x + 3) < FIELD_WIDTH){
					pos_x += 3;
				}
			}
		}
	}

	return 0;
}

int randomNumber(){
	int rando = rand() % 4 + 1; //random number from 1-4
	return rando;
}
