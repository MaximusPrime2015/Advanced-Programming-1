/*
 * producer.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "producer.h"

Producer::Producer(std::string id, std::string name, int age, std::string gender, std::string jobDescription):
Professional::Professional(id, name, age, gender, jobDescription)
{}

std::string Producer::printProfessional(){
	return name;
}

Producer::~Producer(){}
