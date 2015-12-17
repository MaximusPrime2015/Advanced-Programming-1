/*
 * professionalFactory.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "professionalFactory.h"
#include "professional.h"
#include "actor.h"
#include "director.h"
#include "producer.h"
#include "screenwriter.h"

Professional* ProfessionalFactory::create(std::string id, std::string name, int age, std::string gender,
			std::string jobDescription, int profType){
	switch (profType) {
		// Director
		case 0:
			return new Director(id, name, age, gender, jobDescription);
			break;

		// Actor
		case 1:
			return new Actor(id, name, age, gender, jobDescription);
			break;

		// Screen writer
		case 2:
			return new Screenwriter(id, name, age, gender, jobDescription);
			break;

		// Producer
		case 3:
			return new Producer(id, name, age, gender, jobDescription);
			break;

		default:
			std::cout << "Error: invalid professional type" << std::endl;
			break;
	}
	return NULL;
}
