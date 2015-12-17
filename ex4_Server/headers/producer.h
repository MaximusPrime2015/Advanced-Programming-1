/*
 * producer.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef PRODUCER_H_
#define PRODUCER_H_
#include "professional.h"

class Producer: public Professional
{
	public:
	//---------------------------------------------
	//| Action: Creates an instance of Producer.
	//| Input: ID, name, age, gender, and job description.
	//| Returns: none.
	//---------------------------------------------
	Producer(std::string id, std::string name, int age, std::string gender,
			std::string jobDescription);

	//---------------------------------------------
	//| Action: prints the Producer's job description.
	//| Input: none.
	//| Returns: Producer's job description.
	//---------------------------------------------
	std::string printProfessional();

	~Producer();
};

#endif /* PRODUCER_H_ */
