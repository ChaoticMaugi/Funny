#ifndef FIELD_H
#define FIELD_H
#include "person.h"

class field{
private:
	bool hasPerson;
	person owner;

public:
	field(int);
	int id;
	field(bool, person);
	field(bool);
	bool getHasPerson();
	person getOwner();
	void setOwner(person);
	void setHasPerson(bool);

};

#endif
