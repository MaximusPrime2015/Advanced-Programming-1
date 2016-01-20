/*
 * movie.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef MOVIE_H_
#define MOVIE_H_
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Professional;

class Movie
{
private:
	std::string code;
	std::string name;
	int length;
	int rlsYear;
	float rating;
	std::vector<std::string> genres;
	std::vector<Professional*> professionals;
	std::string summary;
	std::string imageURL;
	void setGenreVector(std::vector<std::string> genreVec);
	void setProsVector(std::vector<Professional*> pros);
public:
	//---------------------------------------------
	//| Action: creates an instance of a Movie.
	//| Input: code, name, length, release year, rating and summary.
	//| Returns: none.
	//---------------------------------------------
	Movie(std::string code, std::string name, int length, int rlsYear, float rating, std::string givenImageURL,
	std::string summary);

	//---------------------------------------------
	//| Action: gets the code of the Movie.
	//| Input: none.
	//| Returns: Movie's code.
	//---------------------------------------------
	std::string getCode() const;

	//---------------------------------------------
	//| Action: gets the rating of the Movie.
	//| Input: none.
	//| Returns: Movie's rating.
	//---------------------------------------------
	float getRating();

	//---------------------------------------------
	//| Action: gets the release year of the Movie.
	//| Input: none.
	//| Returns: Movie's release year.
	//---------------------------------------------
	int getReleaseYear();

	//---------------------------------------------
	//| Action: gets the length of the Movie.
	//| Input: none.
	//| Returns: Movie's length.
	//---------------------------------------------
	int getLength();

	//---------------------------------------------
	//| Action: gets the name of the Movie.
	//| Input: none.
	//| Returns: Movie's name.
	//---------------------------------------------
	std::string getName();

	//---------------------------------------------
	//| Action: gets the summary of the Movie.
	//| Input: none.
	//| Returns: Movie's summary.
	//---------------------------------------------
	std::string getSummary();

	std::string getImageURL();

	//---------------------------------------------
	//| Action: returns genre vector.
	//| Input: none.
	//| Returns: genre vector.
	//---------------------------------------------
	std::vector<std::string>* getGenreVec();

	//---------------------------------------------
	//| Action: returns professionals vector.
	//| Input: none.
	//| Returns: professionals vector.
	//---------------------------------------------
	std::vector<Professional*>* getProfessionals();

	//---------------------------------------------
	//| Action: sorts professionals according to a given order.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	void sortProfessionals(int order);

	//---------------------------------------------
	//| Action: prints the Movie's details.
	//| Input: none.
	//| Returns: string containing movie's details.
	//---------------------------------------------
	std::string printMovie();

	//---------------------------------------------
	//| Action: prints the info of all professionals in the movie.
	//| Input: none.
	//| Returns: string containing the data.
	//---------------------------------------------
	std::string printProfessionals();

	//---------------------------------------------
	//| Action: prints the genres of the movie.
	//| Input: none.
	//| Returns: string containing the data.
	//---------------------------------------------
	std::string printGenresList();

	//---------------------------------------------
	//| Action: adds a genre to the movie.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	void addGenre(std::string genre);

	//---------------------------------------------
	//| Action: adds a professional to the movie.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	void addProfessional(Professional* pro);

	//---------------------------------------------
	//| Action: finds a professional in the professionals vector.
	//| Input: professional's id.
	//| Returns: iterator pointing to the pro's location.
	//---------------------------------------------
	std::vector<Professional*>::iterator findProfessional(std::string id);

	//----------------------------------------------------------------------------------
	//| Action: checks if a given iterator has next element in the professionals vector.
	//| Input: professionals vector iterator.
	//| Returns: true if has next; false otherwise.
	//----------------------------------------------------------------------------------
	bool proIteratorHasNext(std::vector<Professional*>::iterator proIT);

	//------------------------------------------------
	//| Action: deletes a professional from the movie.
	//| Input: professional's id.
	//| Returns: none.
	//------------------------------------------------
	void deleteProfessional(std::string proID);

	//------------------------------------------------
	//| Action: compares current movie with another.
	//| Input: another movie.
	//| Returns: true if equal; false otherwise.
	//------------------------------------------------
	bool operator==(const Movie& pro) const;

	//---------------------------------------------
	//| Action: merges current Movie with another.
	//| Input: another movie.
	//| Returns: the merged Movie.
	//---------------------------------------------
	Movie* mergeWith(Movie* Movie);
};

#endif /* MOVIE_H_ */
