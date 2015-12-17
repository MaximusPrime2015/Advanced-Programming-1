/*
 * director.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef ACTOR_H_
#define ACTOR_H_
#include "professional.h"

class Actor: public Professional
{
public:
	//---------------------------------------------
	//| Action: Creates an instance of a Director.
	//| Input:ID, name, age, gender, and job description.
	//| Returns: none.
	//---------------------------------------------
	Actor(std::string id,std::string name, int age, std::string gender, std::string jobDescription);

	//---------------------------------------------
	//| Action: prints the Director's job description.
	//| Input: none.
	//| Returns: Director's job description.
	//---------------------------------------------
	std::string printProfessional();

	~Actor();
};

#endif /* ACTOR_H_ */
