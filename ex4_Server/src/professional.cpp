/*
 * professional.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "professional.h"
#include "movie.h"

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

std::string Professional::getID() const{
	return id;
}

std::string Professional::getName() const{
	return name;
}

int Professional::getAge() const{
	return age;
}

std::string Professional::getGender() const{
	return gender;
}

std::vector<Movie*>* Professional::getMovies(){
	return &movies;
}

int Professional::getMovieListSize() const{
	return movies.size();
}

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

Professional::~Professional(){}
