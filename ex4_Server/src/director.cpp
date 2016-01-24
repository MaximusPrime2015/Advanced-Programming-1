/*
 * director.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "director.h"
Director::Director(std::string id, std::string name, int age, std::string gender, std::string jobDescription):
Professional::Professional(id, name, age, gender, jobDescription)
{}

/*
 * returns director description.
 */
std::string Director::printProfessional(){
	return "@"+name;
}

Director::~Director(){}
