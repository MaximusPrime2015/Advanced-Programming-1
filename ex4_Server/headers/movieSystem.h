/*
 * movieSystem.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef MOVIESYSTEM_H_
#define MOVIESYSTEM_H_
#include <list>
#include <map>
#include <string>
#include "movie.h"
#include "professional.h"
typedef std::vector<Movie*> movieVec;
typedef std::vector<Professional*> proVec;
typedef std::map<std::string, movieVec* > genreToMovieMap;

class MovieSystem
{
private:
	movieVec Movies;
	proVec Professionals;
	genreToMovieMap genreToMovies;
	//movieToGenreMap movieToGenre;
	//movieWithProfessionalMap MoviesWithProfessionals;
public:
	enum sortTypes {byID, byAge, byNumOfMovies};
	enum profTypes {Actor, Director, Producer, Screenwriter};
	//---------------------------------------------
	//| Action: adds a Movie to the system.
	//| Input: Movie's code, name, length, release year, rating and summary.
	//| Returns: none.
	//---------------------------------------------
	void addMovie(std::string code, std::string name, int length, int rlsYear, float
	rating, std::string summary);

	//---------------------------------------------
	//| Action: adds a Professional to the system.
	//| Input: Professional's ID, name, age, gender, job description, and
	//| type.
	//| Returns: none.
	//---------------------------------------------
	void addProfessional(std::string id, std::string name, int age, std::string gender,
			std::string jobDescription, int profType);

	//---------------------------------------------
	//| Action: adds an existing Professional to an existing Movie in the
	//| system.
	//| Input: a Movie's code, and Professional's ID.
	//| Returns: none.
	//---------------------------------------------
	void addProfessionalToMovie(std::string MovieCode, std::string profID);

	//---------------------------------------------
	//| Action: adds an existing Movie to a genre(creates a new genre entry
	//| if the given value does not exist).
	//| Input: Movie's code, and an int that represnts the genre.
	//| Returns: none.
	//---------------------------------------------
	std::string addMovieToGenre(std::string MovieCode, std::string genre);

	//---------------------------------------------
	//| Action: sorts the list of Professionals in a Movie according to a
	//| value from the enum.
	//| Input: Movie code, and a value from the enum.
	//| Returns: none.
	//---------------------------------------------
	std::string sortMovieProfessionals(std::string MovieCode, int order);

	//---------------------------------------------
	//| Action: Prints Professionals from a Movie.
	//| Input: Movie code.
	//| Returns: none.
	//---------------------------------------------
	std::string printMovieProfessionals(std::string MovieCode);

	//---------------------------------------------
	//| Action: prints a Movie's details.
	//| Input: Movie code.
	//| Returns: none.
	//---------------------------------------------
	std::string printMovie(std::string MovieCode);

	//---------------------------------------------
	//| Action: merges 2 Movies.
	//| Input: set of Movies.
	//| Returns: none.
	//---------------------------------------------
	void mergeMovies(std::vector<std::string> MovieCodes);

	//---------------------------------------------
	//| Action: prints Movies with a certain Professional.
	//| Input: Professional's ID.
	//| Returns: none.
	//---------------------------------------------
	std::string printMoviesWithProfessional(std::string id);

	//---------------------------------------------
	//| Action: deletes a Movie from the system.
	//| Input: Movie code.
	//| Returns: none.
	//---------------------------------------------
	void deleteMovie(std::string code);

	//---------------------------------------------
	//| Action: deletes a Professional from the system.
	//| Input: Professionals code.
	//| Returns: none.
	//---------------------------------------------
	void deleteProfessional(std::string code);

	//---------------------------------------------
	//| Action: deletes a Professional from a Movie.
	//| Input: Movie code, Professional's ID.
	//| Returns: none.
	//---------------------------------------------
	std::string deleteProfessionalFromMovie(std::string MovieCode, std::string profID);

	//---------------------------------------------
	//| Action: prints the Movies in the system.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	std::string printMoviesList();

	//---------------------------------------------
	//| Action: prints the Professionals in the system.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	std::string printProfessionalsList();

	//---------------------------------------------
	//| Action: prints the movies by genre.
	//| Input: a genre.
	//| Returns: none.
	//---------------------------------------------
	std::string printMoviesByGenre(std::string genre);

	//---------------------------------------------
	//| Action: starts the system.
	//| Input: none.
	//| Returns: none.
	//---------------------------------------------
	void start();
};

#endif /* MOVIESYSTEM_H_ */
