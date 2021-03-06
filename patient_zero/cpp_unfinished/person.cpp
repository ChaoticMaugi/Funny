#include <iostream>
#include <stdlib.h>
#include "person.h"

//define constants
const float person::MIN_HEAL = 0.2;
const float person::MAX_HEAL = 0.7;

//basic constructor
person::person() {
	std::cout << "person basic constructor is called" << std::endl;
	infectious = 0.;
	healing = 0.;
	infected = false;
}

//constructor with input
person::person(float infection_risk, float severity){
	std::cout << "person constructor with inputs is called" << std::endl;
	setInfectious(infection_risk);
	setHealing(severity);
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
	std::cout << "getInfected gives back: " << this->infected << std::endl;
	return this->infected;
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
	std::cout << "infected changed to: " << b << std::endl;
	infected = b;
	std::cout << "infected is now: " << this->infected << std::endl;
}

void person::setInfectious(float infection_risk){
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
		infectious = inf;
	}
	else{
		infectious = 0.;
	}
}

void person::setHealing(float severity){
	float heal; //returns healing
	float healingI; //specific healing_basis of the person
	
	healingI = (MAX_HEAL - MIN_HEAL)*randomFloat() + MIN_HEAL; //random float between MIN_HEAL and MAX_HEAL

	//heal is healing - severity
	heal = healingI - severity;

	if(heal > 0.){
		healing = heal;
	}
	else{
		healing = 0.;
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


