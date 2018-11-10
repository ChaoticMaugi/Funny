#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* structure for infection */
typedef struct {
	float infection_risk;
	float severity;
} Infection;

/* structure for person */
typedef struct {
	float infectious;
	float healing;
	int id;
	int pos_height;
	int pos_width;
	int infected; /* 0 = not infected, 1 = infected */
} Person;

/* structure for field */
typedef struct {
	Person pers;
} Field;

/* global variables */
static int id_counter; /* static counter for the id of the persons */
static int healthy_won_counter = 0; /* counter for the wins of the healthy */
static int infected_won_counter = 0; /* counter for the wins of the infected */
const float HEALING = 0.8; /* basic healing factor of every person */
#define HEIGHT 20 /* heigth of the game board */
#define WIDTH 20 /* width of the game board */
#define NUMBER_PERSONS 10 /* number of persons on the field */
#define NUMBER_GAMES 1000 /* number of games to be played */
Person defaultPerson; /* the default person used */

/* functions */
float randomNumber();
void setInfection(Infection*, float, float);
void setPerson(Person*, Infection);
void setPersonPosition(Person*, int, int);
void setDefaultPosition(Person*);
void setField(Field*, Person*);
void printPerson(Person);
void printPlayers(Person[NUMBER_PERSONS]);
void initializeBoard(Field[HEIGHT][WIDTH], Person*);
void printField(Field);
void printBoard(Field[HEIGHT][WIDTH]);
void setPlayers(Person[NUMBER_PERSONS], Infection);
void placePlayers(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS]);
int checkDirectionAndFieldPerson(Field[HEIGHT][WIDTH], int, int, int, int);
void setPlayerOnNewField(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int, int, int);
void checkingAndStartMoving(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int, int, int);
void movePlayers(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int);
int doesNeighbourGetInfected(Person[NUMBER_PERSONS], int);
int doesNeighbourGetHealed(Person[NUMBER_PERSONS], int);
void checkingAndStartHealing(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int, int, int);
void checkingAndStartInfecting(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int, int, int);
void infectNeighbour(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int, int, int);
void healNeighbour(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int, int, int);
void infectPlayers(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int);
void healPlayers(Field[HEIGHT][WIDTH], Person[NUMBER_PERSONS], int);
void play();
int getIdOfToBeChangedPerson(Person, Person[NUMBER_PERSONS]);
int GameIsOver(Person[NUMBER_PERSONS]);
void printWinnerTeam(int);
void createPatientZero(Person[NUMBER_PERSONS], int);


float randomNumber() {
	return (float)rand() / (float)RAND_MAX;
}

void setInfection(Infection* inf, float inf_risk, float sev) {
	(*inf).infection_risk = inf_risk;
	(*inf).severity = sev;
}

void setPerson(Person* pers, Infection inf) {
	(*pers).id = id_counter;
	id_counter++;
	/* the persons can change the infection_risk and severity factor by up to 50% of the initial value */
	(*pers).infectious = inf.infection_risk - randomNumber() * (0.5 * inf.infection_risk);
	(*pers).healing = HEALING - inf.severity + randomNumber() * (0.5 * inf.severity);
	(*pers).infected = 0;
}

void setPersonPosition(Person* pers, int h, int w) {
	(*pers).pos_height = h;
	(*pers).pos_width = w;
}

/* set default person */
void setDefaultPerson(Person* pers) {
	/* create special infection */
	Infection defaultInfection;
	setInfection(&defaultInfection, 0.0, HEALING);
	setPerson(pers, defaultInfection);
	(*pers).id = -1;

}

void setField(Field* f, Person* pers1) {
	(*f).pers = (*pers1);
}

void printPerson(Person pers) {
	printf("The person with id %d has healing %.2f and infectious %.2f and was %d infected \n", pers.id, pers.healing, pers.infectious, pers.infected);
	printf("The person with id %d is at position (%d, %d) \n", pers.id, pers.pos_height, pers.pos_width);
}

void printPlayers(Person players[NUMBER_PERSONS]) {
	for (int i = 0; i < NUMBER_PERSONS; i++) {
		printPerson(players[i]);
	}
}

void initializeBoard(Field b[HEIGHT][WIDTH], Person* defPers) {
	for (int h = 0; h < HEIGHT; h++) {
		for (int w = 0; w < WIDTH; w++) {
			setField(&b[h][w], defPers); /* place the default person on every field */
		}
	}
}

void printField(Field f) {
	printPerson(f.pers);
}

void printBoard(Field b[HEIGHT][WIDTH]) {
	for (int h = 0; h < HEIGHT; h++) {
		for (int w = 0; w < WIDTH; w++) {
			printField(b[h][w]);
		}
	}
}

void setPlayers(Person players[NUMBER_PERSONS], Infection inf) {
	for (int i = 0; i < NUMBER_PERSONS; i++) {
		setPerson(&players[i], inf);
	}
}

void placePlayers(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS]) {
	int randHeight;
	int randWidth;

	/* set randHeight and randWidth to a random value between 0 and HEIGHT/WIDTH */
	randHeight = randomNumber() * HEIGHT;
	randWidth = randomNumber() * WIDTH;

	for (int i = 0; i < NUMBER_PERSONS; i++) {
		while (board[randHeight][randWidth].pers.id != -1) {
			randHeight = randomNumber() * HEIGHT;
			randWidth = randomNumber() * WIDTH;
		}
		setField(&board[randHeight][randWidth], &players[i]);
		setPersonPosition(&players[i], randHeight, randWidth);
		/* printf("Person with id %d placed at (%d, %d) \n", board[randHeight][randWidth].pers.id, randHeight, randWidth); */
	}
}

int checkDirectionAndFieldPerson(Field board[HEIGHT][WIDTH], int h, int w, int dh, int dw) {
	/* h is the specific height, w is the specific width, dh is the change in the height, dw is the change in the width */
	if (h + dh >= 0 && h + dh < HEIGHT && w + dw >= 0 && w + dw < WIDTH) {
		if (board[h + dh][w + dw].pers.id == -1) {
			return 1; /* the field is free and possible */
		}
		return 2; /* the field is possible and not free */
	}
	return 0; /* the field is taken and/or not existing */
} /* returns 1 if the field is possible and free, 2 if the field is possible but not free and 0 if the field is impossible*/

void setPlayerOnNewField(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int dh, int dw, int i) {
	//printf("player with id %d starts at (%d, %d) and moves to (%d, %d) \n", i, players[i].pos_height, players[i].pos_width, players[i].pos_height + dh, players[i].pos_width + dw);
	setDefaultPerson(&board[players[i].pos_height][players[i].pos_width].pers); /* set the default person on the old location */
	//printf("Player position before change: %d, %d \n", players[i].pos_height, players[i].pos_width);
	players[i].pos_height += dh; /* player gets new height */
	players[i].pos_width += dw; /* player gets new width */
	//printf("Player position after change: %d, %d \n", players[i].pos_height, players[i].pos_width);
	setField(&board[players[i].pos_height][players[i].pos_width], &players[i]); /* player is placed at new location */
	//printf("player with id %d was moved on field and has now id %d \n", i, board[players[i].pos_height][players[i].pos_width].pers.id);
}

void checkingAndStartMoving(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i, int dh, int dw) {
	if (checkDirectionAndFieldPerson(board, players[i].pos_height, players[i].pos_width, dh, dw) == 1) {
		setPlayerOnNewField(board, players, dh, dw, i);
	}
}

void movePlayers(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i) {
	int direction; /* move direction */

	direction = randomNumber() * 3 + 1; /* random direction 1 = up, 2 = left, 3 = down, 4 = right */

	switch (direction) {
		case 1:
			checkingAndStartMoving(board, players, i, -1, 0);
			break;
		case 2:
			checkingAndStartMoving(board, players, i, 0, -1);
			break;
		case 3:
			checkingAndStartMoving(board, players, i, 1, 0);
			break;
		case 4:
			checkingAndStartMoving(board, players, i, 0, 1);
			break;
	}
}

int doesNeighbourGetInfected(Person players[NUMBER_PERSONS], int i) {
	float odds = randomNumber();
	
	if (players[i].infectious > odds) {
		return 1; /* neighbour will be infected */
	}
	return 0; /* neighbour won't be infected */
}

int doesNeighbourGetHealed(Person players[NUMBER_PERSONS], int i) {
	float odds = randomNumber();

	if (players[i].healing > odds) {
		return 1; /* neighbour will be healed */
	}
	return 0; /* neighbour won't be healed */
}

void checkingAndStartHealing(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i, int dh, int dw) {
	if (checkDirectionAndFieldPerson(board, players[i].pos_height, players[i].pos_width, dh, dw) == 2) {
		healNeighbour(board, players, i, dh, dw);
	}
}

int getIdOfToBeChangedPerson(Person pers, Person players[NUMBER_PERSONS]) {
	for (int j = 0; j < NUMBER_PERSONS; j++) {
		if (pers.id == players[j].id) {
			return j;
		}
	}
}

void checkingAndStartInfecting(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i, int dh, int dw) {
	if (players[i].infected == 1) {
		if (checkDirectionAndFieldPerson(board, players[i].pos_height, players[i].pos_width, dh, dw) == 2) {
			infectNeighbour(board, players, i, dh, dw);
		}
	}
}

void infectNeighbour(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i, int dh, int dw) {
	int j = getIdOfToBeChangedPerson(board[players[i].pos_height + dh][players[i].pos_width + dw].pers, players); /* id of to be changed player */
	board[players[i].pos_height + dh][players[i].pos_width + dw].pers.infected = 1;
	players[j].infected = 1;
	//printf("Player id %d position (%d, %d) infected player id %d position (%d, %d) \n", i, players[i].pos_height, players[i].pos_width, j, players[j].pos_height, players[j].pos_width);
}

void healNeighbour(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i, int dh, int dw) {
	int j = getIdOfToBeChangedPerson(board[players[i].pos_height + dh][players[i].pos_width + dw].pers, players); /* id of to be changed player */
	board[players[i].pos_height + dh][players[i].pos_width + dw].pers.infected = 0;
	players[j].infected = 0;
	//printf("Player id %d position (%d, %d) healed player id %d position (%d, %d) \n", i, players[i].pos_height, players[i].pos_width, j, players[j].pos_height, players[j].pos_width);
}

void infectPlayers(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i) {
	/* it is possible to infect every neighbour (8) of the player, if he is infected in the first place */
	if (doesNeighbourGetInfected(players, i)) {
		checkingAndStartInfecting(board, players, i, -1, 0); /* up */
		checkingAndStartInfecting(board, players, i, 0, -1); /* left */
		checkingAndStartInfecting(board, players, i, 1, 0); /* down */
		checkingAndStartInfecting(board, players, i, 0, 1); /* right */
		checkingAndStartInfecting(board, players, i, -1, -1); /* up-left */
		checkingAndStartInfecting(board, players, i, -1, 1); /* up-right */
		checkingAndStartInfecting(board, players, i, 1, -1); /* down-left */
		checkingAndStartInfecting(board, players, i, 1, 1); /* down-right */
	}
}

void healPlayers(Field board[HEIGHT][WIDTH], Person players[NUMBER_PERSONS], int i) {
	/* it is only possible to heal 1 of the 4 direct neighbours */
	if (doesNeighbourGetHealed(players, i)) {
		int direction;

		direction = randomNumber() * 3 + 1; /* random number between 1-4 */

		switch (direction) {
		case 1:
			checkingAndStartHealing(board, players, i, -1, 0);
			break;
		case 2:
			checkingAndStartHealing(board, players, i, 0, -1);
			break;
		case 3:
			checkingAndStartHealing(board, players, i, 1, 0);
			break;
		case 4:
			checkingAndStartHealing(board, players, i, 0, 1);
			break;
		}
	}
}

int GameIsOver(Person players[NUMBER_PERSONS]) {
	
	for (int i = 0; i < NUMBER_PERSONS - 1; i++) {
		if (players[NUMBER_PERSONS - 1].infected != players[i].infected) {
			return 0; /* false, game is not over */
		}
	}
	//printWinnerTeam(players[NUMBER_PERSONS-1].infected);
	if (players[NUMBER_PERSONS - 1].infected == 1) {
		infected_won_counter++;
	}
	else {
		healthy_won_counter++;
	}

	return 1; /* true, game is over */
}

void printWinnerTeam(int i) {
	if (i == 1) {
		printf("The infected team has won! The world is doomed! \n");
	}
	else if (i == 0) {
		printf("The healthy team has won! Humanity survived this one! \n");
	}
}

void createPatientZero(Person players[NUMBER_PERSONS], int i) {
	players[i].infected = 1;
}

void play() {
	/* create default person and infection for the game */
	Infection hugala;
	setInfection(&hugala, 0.8, 0.5);
	setDefaultPerson(&defaultPerson);

	/* create game board */
	Field board[HEIGHT][WIDTH];

	/* create persons for the game */
	Person players[NUMBER_PERSONS];
	
	/* initialize board */
	initializeBoard(board, &defaultPerson);

	/* create players */
	setPlayers(players, hugala);

	/* place players randomly on field */
	placePlayers(board, players);
	
	/* create patient zero */
	int randPlayer = randomNumber() * (NUMBER_PERSONS - 1) + 1;
	createPatientZero(players, randPlayer);
	
	/* game loop */
	int round_counter = 0;
	//printPlayers(players);

	while (!GameIsOver(players)) { 
		for (int i = 0; i < NUMBER_PERSONS; i++) {
			movePlayers(board, players, i);
			infectPlayers(board, players, i);
			healPlayers(board, players, i);
		}
		round_counter++;
	}
	//printf("This round lasted %d rounds \n", round_counter);
}

/* main function, actual game/simulation */

int main() {
	srand( time(NULL));

	/* set counter for person id to -1 for default person */
	id_counter = -1;

	/* the game loop */
	for (int i = 0; i < NUMBER_GAMES; i++) {
		play();
	}
	/* print the number of wins for each team */
	printf("the healthy won %d times \n", healthy_won_counter);
	printf("the infected won %d times \n", infected_won_counter);

	printf("Enter '0' to exit\n");
	int exit_var;
	scanf("%d", &exit_var);
	// printf("Hello World!\n");
	return 0;
}
