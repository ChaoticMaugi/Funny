#ifndef PERSON_H
#define PERSON_H

class person{
	float infectious;
	float healing;
	bool infected;
	static const float MIN_HEAL = 0.2; //minimal healing ability without respect to severity
	static const float MAX_HEAL = 0.7; //maximal healing ability without respect to severity
	int pos_x;
	int pos_y;

private:
	float randomFloat();

public:
	person();
	person(float, float);
	float getHealing();
	float getInfectious();
	bool getInfected();
	void printPerson();
	void setInfected(bool);
	int getPosX();
	int getPosY();
	void setPosX(int);
	void setPosY(int);
	float setInfectious(float);
	float setHealing(float);

};

#endif