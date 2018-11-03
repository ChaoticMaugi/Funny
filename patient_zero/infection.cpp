#include <iostream>
#include "infection.h"

//basic constructor
infection::infection(){
	infection_risk = 1.;
	severity = 1.;
}

//constructor with inputs
infection::infection(float inf, float sev){
	infection_risk = inf;
	severity = sev;
}

//getter
float infection::getInfectionRisk(){
	return infection_risk;
}

float infection::getSeverity(){
	return severity;
}

/*
int main(){
	infection fever;
	infection numb(0.5, 0.1);
	std::cout << fever.getInfectionRisk() << std::endl;
	std::cout << numb.getInfectionRisk() << std::endl;
	return 0;
}
*/
