/*
 * movie.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */
#include "movie.h"
#include "professional.h"
#include "CompareFuncs.h"
#include "ComparatorFactory.h"
#include "ComparatorWrapper.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Movie::Movie(std::string givenCode, std::string givenName, int givenLength, int givenRlsYear,
		float givenRating, std::string givenImageURL, std::string givenSummary)
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
	imageURL = givenImageURL;
}

/*
 *	returns movie's code.
 */
std::string Movie::getCode() const {
	return code;
}

/*
 * returns movie's rating.
 */
float Movie::getRating(){
	return rating;
}

/*
 * returns movie's release year.
 */
int Movie::getReleaseYear(){
	return rlsYear;
}

/*
 * returns string with movie's name.
 */
std::string Movie::getName(){
	return name;
}

/*
 *	returns string with movie's summary.
 */
std::string Movie::getSummary(){
	return summary;
}

/*
 *	returns string with movie's details.
 */
std::string Movie::printMovie(){
	std::ostringstream lengthBuffer, rlsYearBuffer,
						ratingBuffer;
	lengthBuffer << length;
	rlsYearBuffer << rlsYear;
	ratingBuffer << rating;

	return code + " " + name + " " + lengthBuffer.str() + " " + rlsYearBuffer.str() +
			" " + ratingBuffer.str() + " " + printGenresList()+ imageURL + " " + summary + "\n" + printProfessionals();
}

/*
 *	returns a string with genres.
 */
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

/*
 *	returns a string containing professionals info.
 */
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

/*
 *	returns movie's length.
 */
int Movie::getLength(){
	return length;
}

/*
 * returns current movie's genre vector.
 */
std::vector<std::string>* Movie::getGenreVec(){
	return &genres;
}

/*
 *	adds a professional to the professionals vector.
 */
void Movie::addProfessional(Professional* pro){
	professionals.push_back(pro);
}

/*
 *	adds a genre to the genre vector.
 */
void Movie::addGenre(std::string genre){
	genres.push_back(genre);
}

/*
 *	searchs for a given professional in the professionals vector.
 */
std::vector<Professional*>::iterator Movie::findProfessional(std::string id){
	std::vector<Professional*>::iterator proIT;
	proIT = find_if(professionals.begin(),professionals.end(), proID_Equal(id));

	return proIT;
}

/*
 *	checks if a given professionals iterator has a next element.
 */
bool Movie::proIteratorHasNext(std::vector<Professional*>::iterator proIT){
	return proIT != professionals.end();
}

/*
 * deletes a given professional from a movie.
 */
void Movie::deleteProfessional(std::string proID){
	professionals.erase(findProfessional(proID));
}

/*
 *	returns professionals vector.
 */
std::vector<Professional*>* Movie::getProfessionals(){
	return &professionals;
}

std::string Movie::getImageURL(){
	return imageURL;
}

/*
 *	sorts professionals vector in current movie.
 */
void Movie::sortProfessionals(int order){
	ComparatorFactory factory;
	Comparator* cmp = factory.create(order);
	ComparatorWrapper cW = *(new ComparatorWrapper(cmp));

	std::sort(professionals.begin(), professionals.end(), cW);
}

/*
 *	compares current movie with another.
 */
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

/*
 *	replace current professionals vector with given one
 */
void Movie::setGenreVector(std::vector<std::string> genreVec){
	genres.clear();
	genres.insert(genres.begin(), genreVec.begin(),genreVec.end());
}

/*
 *	replace current professionals vector with given one.
 */
void Movie::setProsVector(std::vector<Professional*> pros){
	professionals.clear();
	professionals.insert(professionals.begin(), pros.begin(),pros.end());
}

/*
 * merges given movie with current.
 */
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
				,other->getRating(),other->getImageURL() ,other->getSummary());
		movie->setGenreVector(unitedGenres);
		movie->setProsVector(unitedPros);
		// add the movie to each pro's list
		for(proIT = unitedPros.begin(); proIT != unitedPros.end(); proIT++){
			(*proIT)->getMovies()->push_back(movie);
		}
	}else{
		movie = new Movie(newCode, name, length, rlsYear, rating, imageURL, summary);
		movie->setGenreVector(unitedGenres);
		movie->setProsVector(unitedPros);
		// add the movie to each pro's list
		for(proIT = unitedPros.begin(); proIT != unitedPros.end(); proIT++){
			(*proIT)->getMovies()->push_back(movie);
		}
	}

	return movie;
}
