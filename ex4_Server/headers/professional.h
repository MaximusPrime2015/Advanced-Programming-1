/*
 * proffesional.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef PROFFESIONAL_H_
#define PROFFESIONAL_H_
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Movie;

class Professional
{
protected:
	std::string id;
	std::string name;
	int age;
	int amountOfMovies;
	std::string gender;
	std::vector<Movie*> movies;
	std::string jobDescription;
public:
	//---------------------------------------------
	//| Action: Creates an instance of a Professional.
	//| Input: ID, name, age, gender, and job description.
	//| Returns: none.
	//---------------------------------------------
	Professional(std::string id,std::string name, int age, std::string gender, std::string
	jobDescription);

	//---------------------------------------------
	//| Action: gets the ID.
	//| Input: none.
	//| Returns: Professional's ID.
	//---------------------------------------------
	std::string getID() const;

	//---------------------------------------------
	//| Action: gets the Professional's name.
	//| Input: none.
	//| Returns: Professional's name.
	//---------------------------------------------
	std::string getName() const;

	//---------------------------------------------
	//| Action: gets the Professional's age.
	//| Input: none.
	//| Returns: Professional's age.
	//---------------------------------------------
	int getAge() const;

	//---------------------------------------------
	//| Action: gets the Professional's gender.
	//| Input: none.
	//| Returns: Professional's gender.
	//---------------------------------------------
	std::string getGender() const;

	std::vector<Movie*>* getMovies();

	int getMovieListSize() const;

	//---------------------------------------------
	//| Action: prints a professional.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	virtual std::string printProfessional() = 0;

	bool operator==(const Professional &pro) const;

	/*
	 * Destructor.
	 */
	virtual ~Professional();
};

#endif /* PROFFESIONAL_H_ */
