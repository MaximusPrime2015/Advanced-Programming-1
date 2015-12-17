/*
 * movie.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */
#include "movie.h"
#include "professional.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

struct strings_Equal{
	std::string str;
	strings_Equal(const std::string& str) : str(str) {}

    bool operator()(const std::string other) const{
		return other == str;
	}
};

struct proID_Equal{
	std::string ID;
	proID_Equal(const std::string& ID) : ID(ID) {}

    bool operator()(const Professional* pro) const{
    	return ID == pro->getID();
    }
};

Movie::Movie(std::string givenCode, std::string givenName, int givenLength, int givenRlsYear,
		float givenRating, std::string givenSummary)
{
	if (givenCode == ""){
		throw std::invalid_argument("Movie: cannot use empty code" );
	}
	code = givenCode;

	if (givenName == ""){
		throw std::invalid_argument("Movie: cannot use empty name");
	}
	name = givenName;

	if (givenLength < 0){
		throw std::invalid_argument("Movie: cannot use negative length");
	}
	length = givenLength;

	if (givenRlsYear < 0){
		throw std::invalid_argument("Movie: cannot use negative release year");
	}
	rlsYear = givenRlsYear;

	if (givenRating < 0 || givenRating > 10.0){
		throw std::invalid_argument("Movie: cannot use empty rating values below 0 or above 10.0");
	}
	rating = givenRating;

	if (givenSummary == ""){
		throw std::invalid_argument("Movie: cannot use empty summary");
	}
	summary = givenSummary;
}

std::string Movie::getCode() const {
	return code;
}

float Movie::getRating(){
	return rating;
}

int Movie::getReleaseYear(){
	return rlsYear;
}

std::string Movie::getName(){
	return name;
}

std::string Movie::getSummary(){
	return summary;
}

std::string Movie::printMovie(){
	std::ostringstream lengthBuffer, rlsYearBuffer,
						ratingBuffer;
	lengthBuffer << length;
	rlsYearBuffer << rlsYear;
	ratingBuffer << rating;

	return code + " " + name + " " + lengthBuffer.str() + " " + rlsYearBuffer.str() +
			" " + ratingBuffer.str() + " " + printGenresList() + summary + "\n" + printProfessionals();
}

std::string Movie::printGenresList(){
	std::vector<std::string>::iterator it;
	it = genres.begin();
	if (it == genres.end()){
		return "";
	}
	std::string output = *it; ++it;

	while(it != genres.end()){
		output = output + "," + *it;
		++it;
	}
	return output+" ";
}

std::string Movie::printProfessionals(){
	std::vector<Professional*>::iterator it;
	std::string output = "";

	if(professionals.empty()){
		return "";
	}
	for(it = professionals.begin(); it != professionals.end(); ++it){
		output = output + (*it)->printProfessional() + "\n";
	}
	return output;
}

int Movie::getLength(){
	return length;
}

std::vector<std::string>* Movie::getGenreVec(){
	return &genres;
}

std::vector<Professional*>* Movie::getProfessionals(){
	return &professionals;
}

bool Movie::operator==(const Movie& movie) const{
	if (code != movie.code){
		return false;
	}
	if (name != movie.name){
		return false;
	}
	if (length != movie.length){
		return false;
	}
	if (rlsYear != movie.rlsYear){
		return false;
	}
	if (rating != movie.rating){
		return false;
	}
	if (summary != movie.summary){
		return false;
	}
	if(professionals != movie.professionals){
		return false;
	}
	if(genres != movie.genres){
		return false;
	}
	return true;
}

void Movie::setGenreVector(std::vector<std::string> genreVec){
	genres.clear();
	genres.insert(genres.begin(), genreVec.begin(),genreVec.end());
}

void Movie::setProsVector(std::vector<Professional*> pros){
	professionals.clear();
	professionals.insert(professionals.begin(), pros.begin(),pros.end());
}

bool Movie::checkPro(Professional* pro){
	std::vector<Professional*>::iterator it;
	pointer_values_equal<Professional> eq = {pro};

	it = find_if(professionals.begin(),professionals.end(), eq);
	if (it == professionals.end()){
		return false;
	}

	return true;
}

Movie* Movie::mergeWith(Movie* other){
	Movie* movie;
	std::vector<std::string> unitedGenres;
	std::vector<std::string>* otherGenres;
	std::vector<Professional*> unitedPros;
	std::vector<Professional*>* otherPros;
	std::vector<std::string>::iterator stringIT;
	std::vector<std::string>::iterator tempStringIT;
	std::vector<Professional*>::iterator proIT;
	std::vector<Professional*>::iterator tempProIT;


	if (other == NULL){
		return this;
	}
	otherPros = other->getProfessionals();
	otherGenres = other->getGenreVec();
	std::string newCode = code + "_" + other->getCode();

	// unite the genres
	// insert current genres first
	unitedGenres.insert(unitedGenres.end(), genres.begin(), genres.end());
	for(stringIT = otherGenres->begin(); stringIT != otherGenres->end(); stringIT++){
		// search for current genre in otherGenres
		tempStringIT = find_if(genres.begin(), genres.end(), strings_Equal(*stringIT));
		// genre is not found
		if (tempStringIT == genres.end()){
			unitedGenres.push_back(*stringIT);
		}
	}

	// unite professionals
	// insert current pros first
	unitedPros.insert(unitedPros.end(), professionals.begin(), professionals.end());
	for(proIT = otherPros->begin(); proIT != otherPros->end(); proIT++){
		// search for current pro in otherPros
		tempProIT = find_if(professionals.begin(), professionals.end(), proID_Equal((*proIT)->getID()));
		// pro is not found
		if (tempProIT == professionals.end()){
			unitedPros.push_back(*proIT);
		}
	}

	// other is longer
	if(other->getLength() > length){
		movie = new Movie(newCode, other->getName(), other->getLength(), other->getReleaseYear()
				,other->getRating(),other->getSummary());
		movie->setGenreVector(unitedGenres);
		movie->setProsVector(unitedPros);
		// add the movie to each pro's list
		for(proIT = unitedPros.begin(); proIT != unitedPros.end(); proIT++){
			(*proIT)->getMovies()->push_back(movie);
		}
	}else{
		movie = new Movie(newCode, name, length, rlsYear, rating, summary);
		movie->setGenreVector(unitedGenres);
		movie->setProsVector(unitedPros);
		// add the movie to each pro's list
		for(proIT = unitedPros.begin(); proIT != unitedPros.end(); proIT++){
			(*proIT)->getMovies()->push_back(movie);
		}
	}

	return movie;
}

