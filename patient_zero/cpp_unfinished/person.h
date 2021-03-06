#ifndef PERSON_H
#define PERSON_H

class person{
private:
	float infectious;
	float healing;

	static const float MIN_HEAL; //minimal healing ability without respect to severity
	static const float MAX_HEAL; //maximal healing ability without respect to severity
	int pos_x;
	int pos_y;
	float randomFloat();

public:
	person();
	bool infected;
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
	void setInfectious(float);
	void setHealing(float);

};

#endif
