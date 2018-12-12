#include <stdio.h>
#include <stdlib.h>

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

	float hp_regeneration; /* regeneration factor for the hp each round */
	float aggression; /* indicates how hostile the creature reacts towards other creatures */
	float naivety; /* indicates how much the creature ignores the danger and water positions, it can find new water sources and new land marks with this but can also simply die really fast */
	float reproduce_urge; /* the urge to reproduce with another creature around, gets higher with age and lower with higher aggression */
} Creature;

typedef enum {
	GRASS = 1,
	BUSH = 2,
	TREE = 3,
} plantSort;

typedef struct {
	int id;
	int hp; /* if a plant gets eaten it looses hp */
	int MAX_HP;
	int age;
	int MAX_AGE; /* a plant has an age and if that age exceeds the MAX_AGE to plant will die faster (it starts to loose hp each turn and not regenerating) */
	float hp_regeneration;
	plantSort sort;
} Plant;

typedef struct {
	int id;
	int hp; /* if water gets drunken it looses hp */
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
#define START_NUMBER_PLANTS 3000 /* number of plants at the beginning */
#define START_NUMBER_WATER 4000 /* number of water at the beginning */
#define START_AGGRESSION 0.5 /* start value for some attributes */
#define START_NAIVETY 0.5
#define START_REPRODUCE_URGE 0.5
#define START_HP_REGENERATION 2
#define START_MAX_HP 100 /* this is the start value for the hp */
static int id_counter_creature = 0;
static int id_counter_plant = 0;
static int id_counter_water = 0;
static int id_counter_field = 0;
Creature defaultCreature;
Plant defaultPlant;
Water defaultWater; /* the default objects will be an indicater that there is no object of this type  */

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

float randomNumber() {
	return (float)rand() / (float)RAND_MAX;
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

/* simulation start */
void play() {

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
