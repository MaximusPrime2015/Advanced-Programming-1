/*
 * screenwriter.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef SCREENWRITER_H_
#define SCREENWRITER_H_
#include "professional.h"

class Screenwriter: public Professional
{
public:
	//---------------------------------------------
	//| Action: Creates an instance of Screenwriter.
	//| Input: ID, name, age, gender, and job description.
	//| Returns: none.
	//---------------------------------------------
	Screenwriter(std::string id, std::string name, int age, std::string gender,
			std::string jobDescription);

	//---------------------------------------------
	//| Action: prints the Screenwriter's job description.
	//| Input: none.
	//| Returns: Screenwriter's job description.
	//---------------------------------------------
	std::string printProfessional();

	~Screenwriter();
};

#endif /* SCREENWRITER_H_ */
