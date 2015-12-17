/*
 * director.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef DIRECTOR_H_
#define DIRECTOR_H_
#include "professional.h"

class Director: public Professional
{
public:
	//---------------------------------------------
	//| Action: Creates an instance of a Director.
	//| Input:ID, name, age, gender, and job description.
	//| Returns: none.
	//---------------------------------------------
	Director(std::string id,std::string name, int age, std::string gender,
			std::string jobDescription);

	//---------------------------------------------
	//| Action: prints the Director's job description.
	//| Input: none.
	//| Returns: Director's job description.
	//---------------------------------------------
	std::string printProfessional();

	~Director();
};

#endif /* DIRECTOR_H_ */
