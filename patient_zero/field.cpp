#include <iostream>
#include "field.h"
#include "person.h"

field::field(int id){
	std::cout << "field basic constructor is called" << std::endl;
	this->id = id;
	hasPerson = false;
}

field::field(bool b, person p){
	setOwner(p);
	setHasPerson(b);
}

field::field(bool b){
	std::cout << "field constructor with bool input is called" << std::endl;
	setHasPerson(b);
}

void field::setOwner(person p){
	owner = p;
	hasPerson = true;
}

void field::setHasPerson(bool b){
	//std::cout << "hasPerson will be set to: " << b << std::endl;
	hasPerson = b;
	//std::cout << "hasPerson after set: " << hasPerson << std::endl;
}

bool field::getHasPerson(){
	return hasPerson;
}

person field::getOwner(){
	return owner;
}

/*
int main(){
	
	person p(0, 0);
	field f(true, p);
	std::cout << f.getHasPerson() << " " << p.getHealing() << std::endl;
	
	return 0;
}
*/
