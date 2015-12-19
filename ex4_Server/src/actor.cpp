/*
 * actor.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "actor.h"

Actor::Actor(std::string id, std::string name, int age, std::string gender, std::string jobDescription):
Professional::Professional(id, name, age, gender, jobDescription)
{}

/*
 * returns actor's description.
 */
std::string Actor::printProfessional(){
	std::ostringstream ageBuffer;
	ageBuffer << age;

	return name + " " + ageBuffer.str();
}

Actor::~Actor(){}
