#include <iostream>
#include <stdlib.h>
#include "person.h"

//basic constructor
person::person() {
	infectious = 0.;
	healing = 0.;
	infected = false;
}

//constructor with input
person::person(float infection_risk, float severity){
	infectious = setInfectious(infection_risk);
	healing = setHealing(severity);
	infected = false;

}

//getter
float person::getHealing(){
	return healing;
}

float person::getInfectious(){
	return infectious;
}

bool person::getInfected(){
	return infected;
}

//print infos
void person::printPerson(){
std::cout << infected << " " << healing << " " << infectious << std::endl;
}

//setter
void person::setPosX(int x){
	pos_x = x;
}

void person::setPosY(int y){
	pos_y = y;
}

void person::setInfected(bool b){
	infected = b;
}

float person::setInfectious(float infection_risk){
	float inf; //returns infectious
	float change = randomFloat();
	float sign = change; //sign is between 0.0 and 1.0

	//set sign to -1 or 1
	if(sign > 0.5){
		sign = 1.;
	}
	else {
		sign = -1.;
	} 

	change *= 10.; //change between 0.0 and 10.0
	change /= 100.; //change between 0.1 and 0.0

	inf = infection_risk + sign * change;
	
	if(inf > 0.){
		return inf;
	}
	else{
		return 0.;
	}
}

float person::setHealing(float severity){
	float heal; //returns healing
	float healingI; //specific healing_basis of the person
	
	healingI = (MAX_HEAL - MIN_HEAL)*randomFloat() + MIN_HEAL; //random float between MIN_HEAL and MAX_HEAL

	//heal is healing - severity
	heal = healingI - severity;

	if(heal > 0.){
		return heal;
	}
	else{
		return 0.;
	}
}

//get random float between 0.0 and 1.0
float person::randomFloat(){
	float change = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //random float between 0.0 and 1.0
	return change;
}

int person::getPosX(){
	return pos_x;
}

int person::getPosY(){
	return pos_y;
}

/*
int main(){
	
	srand (time(NULL));

	person one;
	person two(0.4, 0.05);
	two.setInfected(true);
	person three(0.4, 0.05);
	person four(0.4, 0.05);
	person five(0.4, 0.05);

	one.printPerson();
	two.printPerson();
	three.printPerson();
	four.printPerson();
	five.printPerson();
	

	return 0;
}
*/

