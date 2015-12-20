/*
 * screenwriter.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "screenwriter.h"

Screenwriter::Screenwriter(std::string id, std::string name, int age, std::string gender, std::string jobDescription):
Professional::Professional(id, name, age, gender, jobDescription)
{}

/*
 * return Screen writer's description.
 */
std::string Screenwriter::printProfessional(){

	return name + " " + jobDescription;
}

Screenwriter::~Screenwriter(){}
