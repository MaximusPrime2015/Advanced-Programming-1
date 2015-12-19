/*
 * professional.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "professional.h"
#include "movie.h"
#include "CompareFuncs.h"
#include <algorithm>

Professional::Professional(std::string givenId, std::string givenName, int givenAge, std::string givenGender,
		std::string givenJobDescription)
{
	amountOfMovies = 0;
	if (givenId == ""){
		throw "Professional: cannot use empty ID";
	}
	id = givenId;

	if (givenName == ""){
		throw "Professional: cannot use empty name";
	}
	name = givenName;

	if (givenAge < 0){
		throw "Professional: cannot use negative age";
	}
	age = givenAge;

	// Political correctness aside..
	if (givenGender != "male" && givenGender != "female"){
		throw "Professional: use only female or male gender";
	}
	gender = givenGender;

	if (givenJobDescription == ""){
		throw "Professional: cannot use empty job description";
	}
	jobDescription = givenJobDescription;
}

/*
 *	returns professional's id.
 */
std::string Professional::getID() const{
	return id;
}

/*
 * returns professional's name.
 */
std::string Professional::getName() const{
	return name;
}

/*
 * returns professional's age.
 */
int Professional::getAge() const{
	return age;
}

/*
 * returns professional's gender.
 */
std::string Professional::getGender() const{
	return gender;
}

/*
 * returns professional's movies vector.
 */
std::vector<Movie*>* Professional::getMovies(){
	return &movies;
}

/*
 * returns professional's movie list size.
 */
int Professional::getMovieListSize() const{
	return movies.size();
}

/*
 * adds a given movie to movies vector.
 */
void Professional::addMovie(Movie* movie){
	movies.push_back(movie);
}

/*
 * deletes a movie from movies vector.
 */
void Professional::deleteMovie(std::string movieCode){
	std::vector<Movie*>::iterator movieIT;
	movieIT = find_if(movies.begin(), movies.end(), movieCode_Equal(movieCode));
	movies.erase(movieIT);
}

/*
 *	compares current pro with another.
 */
bool Professional::operator==(const Professional& pro) const{
	if (id != pro.id){
		return false;
	}
	if (name != pro.name){
		return false;
	}
	if (age != pro.age){
		return false;
	}
	if (gender != pro.gender){
		return false;
	}
	if (jobDescription != pro.jobDescription){
		return false;
	}
	if (movies != pro.movies){
		return false;
	}
	return true;
}

/*
 *
 */
Professional::~Professional(){}
