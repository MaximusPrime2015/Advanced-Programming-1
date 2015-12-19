/*
 * movieSystem.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include <algorithm>
#include <string>
#include "movieSystem.h"
#include "professionalFactory.h"
#include "ComparatorFactory.h"
#include "ComparatorWrapper.h"
#include "CompareFuncs.h"

/*
 *	adds a movie to the system.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::addMovie(std::string code, std::string name,
		int length, int rlsYear, float rating, std::string summary){
	// movie with given code is in the system
	if (find_if(Movies.begin(), Movies.end(), movieCode_Equal(code)) != Movies.end()){
		return "Failure";
	}
	Movie* movie = new Movie(code, name, length, rlsYear, rating, summary);
	Movies.push_back(movie);
	return "Success";
}

/*
 *	adds a professional to the system.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::addProfessional(std::string id, std::string name,
		int age, std::string gender, std::string jobDescription, int profType){
	ProfessionalFactory factory;

	// pro with given id is in the system
	if (find_if(Professionals.begin(), Professionals.end(), proID_Equal(id)) != Professionals.end()){
		return "Failure";
	}
	Professional* pro = factory.create(id, name, age, gender,jobDescription,profType);
	Professionals.push_back(pro);
	return "Success";
}

/*
 *	adds a professional to a movie in the system.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::addProfessionalToMovie(std::string movieCode, std::string profID){
	Professional* pro;
	Movie* movie;
	movieVec::iterator movieGeneralIT;
	proVec::iterator proGeneralIT;
	proVec::iterator proIT;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(movieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		return "Failure";
	}
	movie = *movieGeneralIT;

	proGeneralIT = find_if(Professionals.begin(), Professionals.end(), proID_Equal(profID));
	// pro not found
	if (proGeneralIT == Professionals.end()){
		return "Failure";
	}
	pro = *proGeneralIT;

	// search for pro in the movie's professionals vector
	proIT = movie->findProfessional(profID);

	// pro is in the movie
	if(movie->proIteratorHasNext(proIT)){
		return "Failure";
	}

	pro->addMovie(movie);
	movie->addProfessional(pro);
	// sort professional list
	sortMovieProfessionals(movieCode, 1);

	return "Success";
}

/*
 *	adds a movie to a genre in the system. If the genre does not exist, it is created.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::addMovieToGenre(std::string MovieCode, std::string genre){
	movieVec::iterator movieGeneralIT;
	genreToMovieMap::iterator genreIT;
	movieVec* genre_movies;
	movieVec* newMovieVector;
	Movie* movie;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		return "Failure";
	}
	movie = *movieGeneralIT;
	genreIT = genreToMovies.find(genre);

	// genre does not exist in the system
	if (genreIT == genreToMovies.end()){
		// create a new entry for the genre
		newMovieVector = new movieVec;
		newMovieVector->push_back(movie);
		genreToMovies.insert(std::pair<std::string,movieVec*>(genre,newMovieVector));
		movie->addGenre(genre);
	}else{
		genre_movies = genreIT->second;
		genre_movies->push_back(movie);
		movie->addGenre(genre);
	}
	return "Success";
}

/*
 *	sorts professional list of a movie.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::sortMovieProfessionals(std::string MovieCode, int order){
	movieVec::iterator movieIT;

	movieIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieIT == Movies.end()){
		return "Failure";
	}
	(*movieIT)->sortProfessionals(order);

	return "Success";
}

/*
 *	prints professionals list of a given movie.
 *	returns movie's professionals list if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::printMovieProfessionals(std::string MovieCode){
	movieVec::iterator movieIT;

	movieIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieIT == Movies.end()){
		return "Failure";
	}
	return (*movieIT)->printProfessionals();
}

/*
 *	prints a given movie's details.
 *	returns movie's details if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::printMovie(std::string MovieCode){
	movieVec::iterator movieIT;

	movieIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieIT == Movies.end()){
		return "Failure";
	}
	return (*movieIT)->printMovie();
}

/*
 *	merges multiple movies.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::mergeMovies(std::vector<std::string> movieCodes){
	Movie* movie;
	Movie* tempMovie;
	int counter = 0;
	movieVec::iterator movieIT;
	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator auxGenreIT;
	std::vector<std::string>* genreVec;

	it = movieCodes.begin();
	movieIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(*it));
	if (movieIT == Movies.end()){
		return "Failure";
	}

	movie = *movieIT;
	it++;
	counter++;
	while (it != movieCodes.end()){
		movieIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(*it));
		if (movieIT == Movies.end()){
			return "Failure";
		}
		tempMovie = movie;
		movie = movie->mergeWith(*movieIT);
		// when counter = 1, tempMovie is an existing movie in the system which we don't want to delete
		// when counter is > 1, it points to a merged movie(not the final result), and thus can be deleted.
		if (counter > 1){
			delete tempMovie;
		}
		counter++;
		it++;
	}
	Movies.push_back(movie);

	genreVec = movie->getGenreVec();
	for (auxGenreIT = genreVec->begin(); auxGenreIT != genreVec->end(); auxGenreIT++){
		// add the new movie to genres
		(genreToMovies.find(*auxGenreIT)->second)->push_back(movie);
	}
	return "Success";
}

/*
 *	prints movies that have a given professional in their data.
 *	returns a string of the applicable movies if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::printMoviesWithProfessional(std::string id){
	movieVec::iterator mIT;
	proVec::iterator pIT;
	Professional* pro;
	std::string output = "";

	pIT = find_if(Professionals.begin(),Professionals.end(), proID_Equal(id));
	if (pIT == Professionals.end()){
		return "Failure\n";
	}
	pro = *pIT;
	for(mIT = pro->getMovies()->begin(); mIT != pro->getMovies()->end(); mIT++){
		output = output + (*mIT)->printMovie();
	}
	return output;
}

/*
 *	deletes a given movie from the system.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::deleteMovie(std::string movieCode){
	Movie* movie;
	movieVec::iterator movieGeneralIT;
	movieVec::iterator movieIT;
	genreToMovieMap::iterator genreIT;
	movieVec* movieVector;
	proVec::iterator proIT;
	proVec* proVector;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(movieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		return "Failure";
	}
	movie = *movieGeneralIT;
	proVector = movie->getProfessionals();

	// Delete movie from each professional
	for(proIT = proVector->begin();proIT != proVector->end(); proIT++){
		(*proIT)->deleteMovie(movieCode);
	}

	// Delete movie from genre map
	for(genreIT = genreToMovies.begin(); genreIT != genreToMovies.end(); genreIT++){
		movieVector = genreIT->second;
		movieIT = find_if(movieVector->begin(), movieVector->end(), movieCode_Equal(movieCode));
		if (movieIT != movieVector->end()){
			movieVector->erase(movieIT);
		}
	}
	// Delete the movie
	Movies.erase(movieGeneralIT);
	return "Success";
}

/*
 *	deletes a given professional from the system.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::deleteProfessional(std::string proID){
	Professional* pro;
	proVec::iterator proGeneralIT;
	proVec::iterator proIT;
	movieVec::iterator movieIT;
	movieVec* movieVector;

	proGeneralIT = find_if(Professionals.begin(), Professionals.end(), proID_Equal(proID));
	// movie not found
	if (proGeneralIT == Professionals.end()){
		return "Failure";
	}
	pro = *proGeneralIT;
	movieVector = pro->getMovies();

	// Delete pro from each movie
	for(movieIT = movieVector->begin();movieIT != movieVector->end(); movieIT++){
		deleteProfessionalFromMovie((*movieIT)->getCode(), proID);
	}
	// Delete the pro
	Professionals.erase(proGeneralIT);
	return "Success";
}

/*
 *	deletes a given professional from a movie the system.
 *	returns "Success" if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::deleteProfessionalFromMovie(std::string MovieCode, std::string profID){
	Movie* movie;
	movieVec::iterator movieGeneralIT;
	proVec::iterator proIT;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		return "Failure";
	}
	movie = *movieGeneralIT;
	proIT = movie->findProfessional(profID);

	// pro not found
	if (!movie->proIteratorHasNext(proIT)){
		return "Failure";
	}
	movie->deleteProfessional(profID);
	return "Success";
}

/*
 *	prints the details of all the movies in the system.
 *	returns a string containing the data if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::printMoviesList(){
	movieVec::iterator mIT;
	std::string output = "";

	for(mIT = Movies.begin(); mIT != Movies.end(); mIT++){
		output = output + (*mIT)->printMovie();
		}
	return output;
}

/*
 *	prints the details of all the professionals in the system.
 *	returns a string containing the data if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::printProfessionalsList(){
	proVec::iterator pIT;
	std::string output = "";

	for(pIT = Professionals.begin(); pIT != Professionals.end(); pIT++){
		output = output + (*pIT)->printProfessional() + "\n";
		}
	return output;
}

/*
 *	prints the details of all the movies in a given genre in the system.
 *	returns a string containing the data if operation succeeded.
 *	return "Failure" if operation failed.
 */
std::string MovieSystem::printMoviesByGenre(std::string genre){
	movieVec::iterator mIT;
	genreToMovieMap::iterator gIT;
	std::string output = "";

	gIT = genreToMovies.find(genre);
	if(gIT == genreToMovies.end()){
		return "Failure";
	}
	gIT->second;
	for(mIT = gIT->second->begin(); mIT != gIT->second->end(); mIT++){
		output = output + (*mIT)->printMovie();
		}
	return output;
}

/*
 * split a string into tokens.
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

/*
 * start function for the system.
 * handles data from the client.
 */
void MovieSystem::start(){
	using namespace std;
	genreToMovieMap::iterator it;
	movieVec::iterator mIT;
	std::vector<std::string> parsed;
	int command;
	string movieCode;
	string movieName;
	int movieLength;
	int movieReleaseYear;
	float movieRating;
	string movieDescription;
	string genre;
	string moviesToMerge;
	int sortOrder;

	int proType;
	string proID;
	int proAge;
	string proSpecDesc;
	string proGender;
	string proName;
	string temp;

	cin >> command;
	while(command){
		switch (command) {
			case -1:
				return;
			case 1:
				cin >> movieCode;
				movieName = "";
				cin >> temp;
				while(!isdigit(temp[0])){
					if(movieName == ""){
						movieName = temp;
						cin >> temp;
					}else{
						movieName = movieName + " " + temp;
						cin >> temp;
					}
				}
				movieLength = atoi(temp.c_str());
				cin >> movieReleaseYear;
				cin >> movieRating;
				// skip whitespace preceding movie description
				ws(cin);
				getline(std::cin, movieDescription);
				cout << addMovie(movieCode, movieName, movieLength, movieReleaseYear, movieRating, movieDescription) << endl;
				break;

			case 2:
				cin >> proType;
				cin >> proID;
				cin >> proAge;
				// start of description
				cin >> temp;
				proSpecDesc = "";
				while(temp != "male" && temp != "female"){
					proSpecDesc = proSpecDesc + temp;
					cin >> temp;
				}
				// temp is now "male" or "female"
				proGender = temp;
				ws(cin);
				getline(std::cin, proName);
				cout << addProfessional(proID, proName, proAge, proGender, proSpecDesc, proType) << endl;
				break;
			case 3:
				cin >> movieCode;
				cin >> proID;
				cout << addProfessionalToMovie(movieCode, proID) << endl;
				break;
			case 4:
				cin >> movieCode;
				cin >> genre;
				cout << addMovieToGenre(movieCode, genre) << endl;
				break;
			case 5:
				cin >> movieCode;
				cin >> sortOrder;
				cout << sortMovieProfessionals(movieCode, sortOrder) << endl;
				break;
			case 6:
				cin >> movieCode;
				cout << printMovieProfessionals(movieCode);
				break;
			case 7:
				cin >> movieCode;
				cout << printMovie(movieCode);
				break;
			case 8:
				cin >> moviesToMerge;
				parsed = split(moviesToMerge, ',');
				cout << mergeMovies(parsed) << endl;
				break;
			case 9:
				cin >> proID;
				cout << printMoviesWithProfessional(proID);
				break;
			case 10:
				cin >> movieCode;
				cout << deleteMovie(movieCode) << endl;
				break;
			case 11:
				cin >> proID;
				cout << deleteProfessional(proID) << endl;
				break;
			case 12:
				cin >> movieCode;
				cin >> proID;
				cout << deleteProfessionalFromMovie(movieCode, proID) << endl;
				break;
			case 13:
				cout << printMoviesList();
				break;
			case 14:
				cout << printProfessionalsList();
				break;
			case 15:
				cin >> genre;
				cout << printMoviesByGenre(genre);
				break;
			default:
				break;
		}
		cin >> command;
	}

}
