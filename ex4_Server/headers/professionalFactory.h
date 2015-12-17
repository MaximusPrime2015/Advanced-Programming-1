/*
 * professionalFactory.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef PROFESSIONALFACTORY_H_
#define PROFESSIONALFACTORY_H_
#include "professional.h"

class ProfessionalFactory
{
public:
	//---------------------------------------------
	//| Action: Creates a Professional accodring the recieved type.
	//| Input: ID, name, age, gender, job description, and type.
	//| Returns: Director, Producer, Screenwriter, or Director.
	//---------------------------------------------
	Professional* create(std::string id, std::string name, int age, std::string gender,
			std::string jobDescription, int profType);
};

#endif /* PROFESSIONALFACTORY_H_ */
