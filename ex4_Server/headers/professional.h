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

	//---------------------------------------------
	//| Action: returns movies Vector.
	//| Input: none.
	//| Returns: movies vector.
	//---------------------------------------------
	std::vector<Movie*>* getMovies();

	//---------------------------------------------
	//| Action: returns the movies vector size.
	//| Input: none.
	//| Returns: movies vector size.
	//---------------------------------------------
	int getMovieListSize() const;

	//---------------------------------------------
	//| Action: adds a movie.
	//| Input: movie pointer.
	//| Returns: none.
	//---------------------------------------------
	void addMovie(Movie* movie);

	//---------------------------------------------
	//| Action: deletes a movie.
	//| Input: movie code.
	//| Returns: none.
	//---------------------------------------------
	void deleteMovie(std::string movieCode);

	//---------------------------------------------
	//| Action: prints a professional.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	virtual std::string printProfessional() = 0;

	//---------------------------------------------
	//| Action: compares current professional with another.
	//| Input: reference to another professional.
	//| Returns: true if equal; false otherwise.
	//---------------------------------------------
	bool operator==(const Professional &pro) const;

	/*
	 * Destructor.
	 */
	virtual ~Professional();
};

#endif /* PROFFESIONAL_H_ */
