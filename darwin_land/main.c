#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* structures for all the different things */
typedef struct {
	int id;
	int hp; /* if it drops to 0, the creature will die */
	int MAX_HP; /* maximum possible hp for this object */
	int age; /* with age near the MAX_AGE teh creature gets less aggressive, but the creature is also less affected by hunger and thirst */
	int MAX_AGE; /* if the creature exceeds its MAX_AGE it will stop regenerating hp each round and starts loosing it */
	int danger_pos_x;
	int danger_pos_y; /* danger coordinates point to the point where the creature has last been in danger */
	int water_pos_x;
	int water_pos_y; /* water coordinates point to the last known water source the creature has found */
	int berserker; /* the berserker mode starts once a creature hits a small hp number, nearly 0, then the creature will enrage and its naivety and aggression will rise extremly. This will be handeled as a boolean value */
	int hunger; /* indicates if the creature is hungry (100) or not hungry (0), if a creature gets hungry it will become more aggressive and naive */
	int thirst; /* indicates if the creature is thirsty (100) or not thirsty (0), if a creature gets thirsty it will move more likely to water position and will become more aggressive and naive */
	int canSwim; /* the ability to swim, 1 = true, 0 = false */
	int attack; /* indicates how much damage is dealt to other creatures in battle */

	float hp_regeneration; /* regeneration factor for the hp each round */
	float aggression; /* indicates how hostile the creature reacts towards other creatures */
	float naivety; /* indicates how much the creature ignores the danger and water positions, it can find new water sources and new land marks with this but can also simply die really fast */
	float reproduce_urge; /* the urge to reproduce with another creature around, gets higher with age and lower with higher aggression */
} Creature;

typedef struct {
	int id;
	int hp; /* if a plant gets eaten it looses hp */
	int MAX_HP;
	int age;
	int MAX_AGE; /* a plant has an age and if that age exceeds the MAX_AGE the plant will die faster (it starts to loose hp each turn and not regenerating) */
	float hp_regeneration;
} Plant;

typedef struct {
	int id;
	int hp; /* if water gets drunken it looses hp */
	int MAX_HP;
	float hp_regeneration;
} Water;

typedef struct {
	int id;
	Plant fPlant;
	Water fWater;
	Creature fCreature;
} Field;

/* constants and constant variables */
#define HEIGHT 100 /* height of the map */
#define WIDTH 100 /* width of the map */
#define START_NUMBER_CREATURES 100 /* number of creatures at the beginning */
#define START_NUMBER_PLANTS 4000 /* number of plants at the beginning */
#define START_NUMBER_WATER 3000 /* number of water at the beginning */
#define START_AGGRESSION 0.5 /* start value for some attributes */
#define START_NAIVETY 0.5
#define START_REPRODUCE_URGE 0.5
#define START_HP_REGENERATION 2
#define START_ATTACK 20
#define START_MAX_HP 100 /* this is the start value for the hp */
#define START_MAX_AGE_CREATURE 150
#define START_MAX_AGE_PLANT 50
#define START_CHILD_FLUCTUATION 0.3 /* this is the maximum possible fluctuation of the start values and of children */
#define NUMBER_OF_TURNS 100 /* defines the number of turns until the game stops because there is no other way to declare the simulation over */
static int id_counter_creature = 0;
static int id_counter_plant = 0;
static int id_counter_water = 0;
static int id_counter_field = 0;
Creature defaultCreature;
Plant defaultPlant;
Water defaultWater; /* the default objects will be an indicater that there is no object of this type  */
Field board[HEIGHT][WIDTH]; /* the game board */

/* used functions */
void play();
float randomNumber(); /* generates a random number between 0.0 and 1.0 */
void createCreature(Creature*);
void setDefaultCreature(Creature*);
void setCreatureId(Creature*); /* gives an id to a creature */
void createPlant(Plant*);
void setDefaultPlant(Plant*);
void setPlantId(Plant*);
void createWater(Water*); /* createXX() is used only at the beginning of the simulation for the creation of the start creatures, after that there will only be new objects by reproducing */
void setDefaultWater(Water*); /* createDefaultXX() is used only for the creation of the default objects of each type */
void setWaterId(Water*);
void createChildCreature(Creature, Creature, Creature*); /* uses 2 parent creatures and sets the creature* (child) attributes to a mixture of the parent attributes */
void createChildPlant(Plant, Plant*);
void createChildWater(Water, Water*); /* plant and water only need one parent because each field can expend */
void setCreatureAttributes(Creature*, int, int, int, int, float, float, float, float, int, int, int, int);
void setPlantAttributes(Plant*, int, int, float);
void setWaterAttributes(Water*, int, float);
int intFluctuate(int);
float floatFluctuate(float);
void printCreature(Creature);

void printCreature(Creature c) {
	printf("Max hp: %d \n", c.MAX_HP);
	printf("Max age: %d \n", c.MAX_AGE);
	printf("naivety: %f \n", c.naivety);
}

int intFluctuate(int i) {
	int sign;
	sign = (randomNumber() + 0.5); /* 0 or 1, 0 is -1 and 1 is 1 */

	if (sign == 0) {
		i = i - i * START_CHILD_FLUCTUATION*randomNumber();
		return i;
	}

	i = i + i * START_CHILD_FLUCTUATION*randomNumber();
	return i;
}

float floatFluctuate(float i) {
	int sign;
	sign = (randomNumber() + 0.5); /* 0 or 1, 0 is -1 and 1 is 1 */

	if (sign == 0) {
		i = i - i * START_CHILD_FLUCTUATION*randomNumber();
		return i;
	}

	i = i + i * START_CHILD_FLUCTUATION*randomNumber();
	return i;
}

void setCreatureAttributes(Creature* c, int cMax_hp, int cMax_age, int cCan_swim, int cattack, float chp_rege, float caggre, float cnaive, float creproduce, int water_x, int water_y, int danger_x, int danger_y) {
	(*c).MAX_HP = cMax_hp;
	(*c).MAX_AGE = cMax_age;
	(*c).canSwim = cCan_swim;
	(*c).attack = cattack;
	(*c).hp_regeneration = chp_rege;
	(*c).aggression = caggre;
	(*c).naivety = cnaive;
	(*c).reproduce_urge = creproduce;
	(*c).age = 0;
	(*c).hp = (*c).MAX_HP;
	(*c).water_pos_x = water_x;
	(*c).water_pos_y = water_y;
	(*c).danger_pos_x = danger_x;
	(*c).danger_pos_y = danger_y;
	(*c).hunger = 0;
	(*c).thirst = 0;
}

void setPlantAttributes(Plant* p, int pMax_hp, int pMax_age, float php_rege) {
	(*p).MAX_AGE = pMax_age;
	(*p).MAX_HP = pMax_hp;
	(*p).hp_regeneration = php_rege;
	(*p).age = 0;
	(*p).hp = (*p).MAX_HP;
}

void setWaterAttributes(Water* w, int wMax_hp, float whp_rege) {
	(*w).MAX_HP = wMax_hp;
	(*w).hp_regeneration = whp_rege;
	(*w).hp = (*w).MAX_HP;
}

float randomNumber() {
	return (float)rand() / (float)RAND_MAX; // random number between 0 and 1
}

void setDefaultPlant(Plant* p){
	(*p).id = -1;
}

void setDefaultWater(Water* w){
	(*w).id = -1;
}

void setDefaultCreature(Creature* c){
	(*c).id = -1;
}

void setPlantId(Plant* p) {
	(*p).id = id_counter_plant;
	id_counter_plant++;
}

void setCreatureId(Creature* c) {
	(*c).id = id_counter_creature;
	id_counter_creature++;
}

void setWaterId(Water* w) {
	(*w).id = id_counter_water;
	id_counter_water++;
}

void createChildCreature(Creature dad, Creature mom, Creature* kid) {
	int max_hp, max_age, attack, canSwim, water_x, water_y, danger_x, danger_y;
	float aggres, naive, hp_rege, reproduce;

	max_hp = intFluctuate((dad.MAX_HP + mom.MAX_HP) / 2);
	max_age = intFluctuate((dad.MAX_AGE + mom.MAX_AGE) / 2);
	attack = intFluctuate((dad.attack + mom.attack) / 2);
	aggres = floatFluctuate((dad.aggression + mom.aggression) / 2);
	naive = floatFluctuate((dad.naivety + mom.naivety) / 2);
	reproduce = floatFluctuate((dad.reproduce_urge + mom.reproduce_urge) / 2);
	hp_rege = floatFluctuate((dad.hp_regeneration + mom.hp_regeneration) / 2);
	if (dad.canSwim == 1) {
		canSwim = 1;
	}
	if (mom.canSwim == 1) {
		canSwim = 1;
	}
	water_x = dad.water_pos_x;
	water_y = dad.water_pos_y;
	danger_x = mom.danger_pos_x;
	danger_y = mom.danger_pos_y;

	setCreatureAttributes(kid, max_hp, max_age, canSwim, attack, hp_rege, aggres, naive, reproduce, water_x, water_y, danger_x, danger_y);
}

void createChildPlant(Plant parent, Plant* kid) {
	int max_hp, max_age;
	float hp_rege;

	max_hp = intFluctuate(parent.MAX_HP);
	max_age = intFluctuate(parent.MAX_AGE);
	hp_rege = floatFluctuate(parent.hp_regeneration);

	setPlantAttributes(kid, max_hp, max_age, hp_rege);
}

void createChildWater(Water parent, Water* kid) {
	int max_hp;
	float hp_rege;

	hp_rege = floatFluctuate(parent.hp_regeneration);
	max_hp = intFluctuate(parent.MAX_HP);

	setWaterAttributes(kid, max_hp, hp_rege);
}

void initializeBoard() {
	int i, j;
	
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			setDefaultCreature(&board[i][j].fCreature);
			setDefaultPlant(&board[i][j].fPlant);
			setDefaultWater(&board[i][j].fWater);
			//printf("id of creature at %d, %d is %d \n", i, j, board[i][j].fCreature.id);
		}
	}
}

void fillBoard() {
	int c, p, w;
	int rand_x, rand_y;
	int canSwim;

	rand_x = randomNumber() * (WIDTH - 1);
	rand_y = randomNumber() * (HEIGHT - 1);
	//printf("random position: %d, %d \n", rand_y, rand_x);

	//create creatures on the field
	for (c = 0; c < START_NUMBER_CREATURES; c++) {
		while (board[rand_y][rand_x].fWater.id != -1 || board[rand_y][rand_x].fCreature.id != -1) { // no spawning on water for creatures or on other creatures
			rand_x = randomNumber() * (WIDTH - 1);
			rand_y = randomNumber() * (HEIGHT - 1);
		}

		setCreatureId(&board[rand_y][rand_x].fCreature);
		//printf("creature with id %d set at %d, %d \n", board[rand_y][rand_x].fCreature.id, rand_y, rand_x);
		canSwim = (randomNumber() + 0.5);
		setCreatureAttributes(&board[rand_y][rand_x].fCreature, intFluctuate(START_MAX_HP), intFluctuate(START_MAX_AGE_CREATURE), canSwim, intFluctuate(START_ATTACK), floatFluctuate(START_HP_REGENERATION), floatFluctuate(START_AGGRESSION), floatFluctuate(START_NAIVETY), floatFluctuate(START_REPRODUCE_URGE), -1, -1, -1, -1);
		//printCreature(board[rand_y][rand_x].fCreature);
	}
}

/* simulation start */
void play() {
	initializeBoard();
	fillBoard();
}

int main(){
	srand(time(NULL));

	setDefaultCreature(&defaultCreature);
	setDefaultWater(&defaultWater);
	setDefaultPlant(&defaultPlant);

	play();

	// printf("Hello World! \n");
	return 0;
}
