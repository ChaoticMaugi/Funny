#ifndef INFECTION_H
#define INFECTION_H

class infection{
	float infection_risk;
	float severity;
public:
	infection();
	infection(float, float);
	float getInfectionRisk();
	float getSeverity();

};

#endif