#include <iostream>
#include "field.h"
#include "person.h"

field::field(){
	hasPerson = false;
}

field::field(bool b, person p){
	setOwner(p);
	setHasPerson(b);
}

void field::setOwner(person p){
	owner = p;
}

void field::setHasPerson(bool b){
	hasPerson = b;
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