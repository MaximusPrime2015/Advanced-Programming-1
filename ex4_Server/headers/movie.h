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
	void setGenreVector(std::vector<std::string> genreVec);
	void setProsVector(std::vector<Professional*> pros);
public:
	//---------------------------------------------
	//| Action: creates an instance of a Movie.
	//| Input: code, name, length, release year, rating and summary.
	//| Returns: none.
	//---------------------------------------------
	Movie(std::string code, std::string name, int length, int rlsYear, float rating,
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

	std::vector<std::string>* getGenreVec();

	std::vector<Professional*>* getProfessionals();

	//---------------------------------------------
	//| Action: prints the Movie's details.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	std::string printMovie();

	std::string printProfessionals();

	std::string printGenresList();

	bool checkPro(Professional* pro);

	bool operator==(const Movie& pro) const;

	//---------------------------------------------
	//| Action: merges current Movie with another.
	//| Input: none.
	//| Returns: the merged Movie.
	//---------------------------------------------
	Movie* mergeWith(Movie* Movie);
};

template <typename T>
struct pointer_values_equal{
    const T* to_find;

    bool operator()(const T* other) const
    {
        return *to_find == *other;
    }
};

#endif /* MOVIE_H_ */
