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
#define	skipSpace index++

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
	try{
	Movie* movie = new Movie(code, name, length, rlsYear, rating, summary);
	Movies.push_back(movie);
	return "Success";
	}
	catch (std::string &e) {
		return "Failure";
	}
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
	try{
	Professional* pro = factory.create(id, name, age, gender,jobDescription,profType);
	Professionals.push_back(pro);
	return "Success";
	}
	catch (std::string &e) {
		return "Failure";
	}
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
	string client_input;
	string output;
	int i, command;

	i = 0;
	getline(std::cin, client_input);
	command = getIntFromStr(client_input, i);
	// increment i so that it points to the first character after the space
	i++;
	while(true){
		switch (command) {
			case -1:
				return;
			case 1:
				output = process_AddMovie(client_input, i);
				break;
			case 2:
				output = process_AddProfessional(client_input, i);
				break;
			case 3:
				output = process_addProfessionalToMovie(client_input, i);
				break;
			case 4:
				output = process_addMovieToGenre(client_input, i);
				break;
			case 5:
				output = process_sortMovieProfessionals(client_input, i);
				break;
			case 6:
				output = process_printMovieProfessionals(client_input, i);
				break;
			case 7:
				output = process_printMovie(client_input, i);
				break;
			case 8:
				output = process_mergeMovies(client_input, i);
				break;
			case 9:
				output = process_printMoviesWithProfessional(client_input, i);
				break;
			case 10:
				output = process_deleteMovie(client_input, i);
				break;
			case 11:
				output = process_deleteProfessional(client_input, i);
				break;
			case 12:
				output = process_deleteProfessionalFromMovie(client_input, i);
				break;
			case 13:
				output = printMoviesList();
				break;
			case 14:
				output = printProfessionalsList();
				break;
			case 15:
				output = process_printMoviesByGenre(client_input, i);
				break;
			default:
				break;
		}
		cout << output << endl;
		i = 0;
		getline(std::cin, client_input);
		command = getIntFromStr(client_input, i);
		// increment i so that it points to the first character after the space
		i++;
	}
}

/*
============================================================================================================
============================================================================================================

									string processing functions

============================================================================================================
============================================================================================================
*/
/*
 * processes command string in the following format:
 * 1 [id] [name] [length] [year] [rating] [desc]
 */
std::string MovieSystem::process_AddMovie(std::string strToProcess, int index){
	std::string movieCode;
	std::string movieName;
	int movieLength = 0;
	int movieReleaseYear = 0;
	int temp;
	float movieRating;
	std::string movieDescription;

	// ID
	movieCode = getString(strToProcess, index);
	skipSpace;

	// movie name
	while(strToProcess[index] != ' ' && (strToProcess[index] > 58 || strToProcess[index] < 48)){
		movieName += strToProcess[index];
		index++;
	}
	skipSpace;

	// movie length
	movieLength = getIntFromStr(strToProcess, index);
	skipSpace;

	// movie release year
	movieReleaseYear = getIntFromStr(strToProcess, index);
	skipSpace;

	// movie Rating
	temp = 0;
	while(strToProcess[index] != ' '){
		//convert char digit to int
		if (strToProcess[index] != '.'){
			temp = temp*10 + (strToProcess[index]-48);
		}else{
			movieRating = temp;
			temp = 0;
		}
		index++;
	}
	movieRating += (temp/10.0);
	skipSpace;

	// movie Description
	movieDescription = getEndOfString(strToProcess, index);

	return addMovie(movieCode, movieName, movieLength, movieReleaseYear, movieRating, movieDescription);
}

/*
 * processes command string in the following format:
 * 2 [type] [id] [age] [specific-desc] [gender] [name]
 */
std::string MovieSystem::process_AddProfessional(std::string strToProcess, int index){
	int proType = 0;
	int proAge = 0;
	std::string proID;
	std::string proName;
	std::string proGender;
	std::string proDescription;

	// type
	proType = getIntFromStr(strToProcess, index);
	skipSpace;

	// ID
	proID = getString(strToProcess, index);
	skipSpace;

	// age
	proAge = getIntFromStr(strToProcess, index);
	skipSpace;

	// specific-desc
	proDescription = getString(strToProcess, index);
	skipSpace;

	// gender
	proGender = getString(strToProcess, index);
	skipSpace;

	// name
	proName = getEndOfString(strToProcess, index);

	return addProfessional(proID, proName, proAge, proGender, proDescription, proType);
}

/*
 * processes command string in the following format:
 * 3 [movie-id] [pro-id]
 */
std::string MovieSystem::process_addProfessionalToMovie(std::string strToProcess, int index){
	std::string movieCode;
	std::string proID;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	// pro id
	proID = getString(strToProcess, index);

	return addProfessionalToMovie(movieCode, proID);
}

/*
 * processes command string in the following format:
 * 4 [movie-id] [genre]
 */
std::string MovieSystem::process_addMovieToGenre(std::string strToProcess, int index){
	std::string movieCode;
	std::string genre;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	genre = getEndOfString(strToProcess, index);
	return addMovieToGenre(movieCode, genre);
}

/*
 * processes command string in the following format:
 * 5 [movie-id] [sort-type]
 */
std::string MovieSystem::process_sortMovieProfessionals(std::string strToProcess, int index){
	std::string movieCode;
	int order;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	// order
	order = getIntFromStr(strToProcess, index);

	return sortMovieProfessionals(movieCode, order);
}

/*
 * processes command string in the following format:
 * 6 [movie-id]
 */
std::string MovieSystem::process_printMovieProfessionals(std::string strToProcess, int index){
	std::string movieCode;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	return printMovieProfessionals(movieCode);
}

/*
 * processes command string in the following format:
 * 7 [movie-id]
 */
std::string MovieSystem::process_printMovie(std::string strToProcess, int index){
	std::string movieCode;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	return printMovie(movieCode);
}

/*
 * processes command string in the following format:
 * 8 [movie-id],...,[movie-id]
 */
std::string MovieSystem::process_mergeMovies(std::string strToProcess, int index){
	std::string moviesToMerge = strToProcess.substr(index, strToProcess.length());
	std::vector<std::string> parsed = split(moviesToMerge, ',');

	return mergeMovies(parsed);
}

/*
 * processes command string in the following format:
 * 9 [pro-id]
 */
std::string MovieSystem::process_printMoviesWithProfessional(std::string strToProcess, int index){
	std::string proID;

	// pro id
	proID = getString(strToProcess, index);
	skipSpace;

	return printMoviesWithProfessional(proID);
}

/*
 * processes command string in the following format:
 * 10 [movie-id]
 */
std::string MovieSystem::process_deleteMovie(std::string strToProcess, int index){
	std::string movieCode;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	return deleteMovie(movieCode);
}

/*
 * processes command string in the following format:
 * 11 [pro-id]
 */
std::string MovieSystem::process_deleteProfessional(std::string strToProcess, int index){
	std::string proID;

	// pro id
	proID = getString(strToProcess, index);
	skipSpace;

	return deleteProfessional(proID);
}

/*
 * processes command string in the following format:
 * 12 [movie-id] [pro-id]
 */
std::string MovieSystem::process_deleteProfessionalFromMovie(std::string strToProcess, int index){
	std::string proID;
	std::string movieCode;

	// movie code
	movieCode = getString(strToProcess, index);
	skipSpace;

	// pro id
	proID = getString(strToProcess, index);

	return deleteProfessionalFromMovie(movieCode, proID);
}

/*
 * processes command string in the following format:
 * 15 [genre]
 */
std::string MovieSystem::process_printMoviesByGenre(std::string strToProcess, int index){
	std::string genre;

	// genre
	genre = getEndOfString(strToProcess, index);

	return printMoviesByGenre(genre);
}

int getIntFromStr(std::string str, int &index){
	int output = 0;
	int flag = 0;

	// if str starts with a negative number
	if(str[index] == '-'){
		flag = 1;
		index++;
	}

	while(str[index] && str[index] != ' '){
		output = output*10 + str[index]-48;
		index++;
	}
	if(flag){ output *= -1; }
	return output;
}

std::string getString(std::string str, int &index){
	std::string output;

	while(str[index] && str[index] != ' '){
		output += str[index];
		index++;
	}
	return output;
}

std::string getEndOfString(std::string str, int &index){
	return str.substr(index, str.length());
}
