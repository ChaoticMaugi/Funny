#ifndef FIELD_H
#define FIELD_H
#include "person.h"

class field{
	bool hasPerson;
	person owner;

public:
	field();
	field(bool, person);
	field(bool);
	bool getHasPerson();
	person getOwner();
	void setOwner(person);
	void setHasPerson(bool);

};

#endif