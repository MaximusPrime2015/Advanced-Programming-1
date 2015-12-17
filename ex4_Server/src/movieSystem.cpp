/*
 * movieSystem.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include <algorithm>
#include "movieSystem.h"
#include "professionalFactory.h"
#include "cmpAge.h"
#include "cmpID.h"
#include "cmpMovieNum.h"
#include <string>

struct movieCode_Equal{
	std::string code;
	movieCode_Equal(const std::string& code) : code(code) {}

    bool operator()(const Movie* movie) const{
		return movie->getCode() == code;
	}
};

struct proID_Equal{
	std::string ID;
	proID_Equal(const std::string& ID) : ID(ID) {}

    bool operator()(const Professional* pro) const{
    	return ID == pro->getID();
    }
};

/*
 *
 */
void MovieSystem::addMovie(std::string code, std::string name,
		int length, int rlsYear, float rating, std::string summary){
	// movie with given code is in the system
	if (find_if(Movies.begin(), Movies.end(), movieCode_Equal(code)) != Movies.end()){
		std::cout << "Failure" << std::endl;
		return;
	}
	Movie* movie = new Movie(code, name, length, rlsYear, rating, summary);
	Movies.push_back(movie);
	std::cout << "Success" << std::endl;
}

/*
 *
 */
void MovieSystem::addProfessional(std::string id, std::string name,
		int age, std::string gender, std::string jobDescription, int profType){
	ProfessionalFactory factory;

	// pro with given id is in the system
	if (find_if(Professionals.begin(), Professionals.end(), proID_Equal(id)) != Professionals.end()){
		std::cout << "Failure" << std::endl;
		return;
	}
	Professional* pro = factory.create(id, name, age, gender,jobDescription,profType);
	Professionals.push_back(pro);
	std::cout << "Success" << std::endl;
}

/*
 *
 */
void MovieSystem::addProfessionalToMovie(std::string movieCode, std::string profID){
	Professional* pro;
	Movie* movie;
	movieVec::iterator movieGeneralIT;
	movieVec* movieVector;
	proVec::iterator proGeneralIT;
	proVec::iterator proIT;
	proVec* proVector;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(movieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		std::cout << "Failure" << std::endl;
		return;
	}
	movie = *movieGeneralIT;

	proGeneralIT = find_if(Professionals.begin(), Professionals.end(), proID_Equal(profID));
	// pro not found
	if (proGeneralIT == Professionals.end()){
		std::cout << "Failure" << std::endl;
		return;
	}
	pro = *proGeneralIT;
	proVector = movie->getProfessionals();
	movieVector = pro->getMovies();

	// search for pro in the movie's professionals vector
	proIT = find_if(proVector->begin(),proVector->end(), proID_Equal(profID));
	// pro is in the movie
	if(proIT != proVector->end()){
		std::cout << "Failure" << std::endl;
		return;
	}
	proVector->push_back(pro);
	movieVector->push_back(movie);
	// sort professional list
	sortMovieProfessionals(movieCode, 1);

	std::cout << "Success" << std::endl;
}

/*
 *
 */
std::string MovieSystem::addMovieToGenre(std::string MovieCode, std::string genre){
	movieVec::iterator movieGeneralIT;
	genreToMovieMap::iterator genreIT;
	movieVec* genre_movies;
	Movie* movie;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		//std::cout << "Failure" << std::endl;
		return "Failure";
	}
	movie = *movieGeneralIT;

	genreIT = genreToMovies.find(genre);
	// genre does not exist in the system
	if (genreIT == genreToMovies.end()){
		// create a new entry for the genre
		movieVec* newMovieVector = new movieVec;
		//newMovieMap->insert(std::pair<std::string,Movie*>(MovieCode,movie));
		newMovieVector->push_back(movie);
		genreToMovies.insert(std::pair<std::string,movieVec*>(genre,newMovieVector));
		movie->getGenreVec()->push_back(genre);
	}else{
		genre_movies = genreIT->second;
		//genreMovies->insert(std::pair<std::string,Movie*>(genre,movie));
		genre_movies->push_back(movie);
		movie->getGenreVec()->push_back(genre);
	}
	//std::cout << "Success" << std::endl;
	return "Success";
}

/*
 *
 */
std::string MovieSystem::sortMovieProfessionals(std::string MovieCode, int order){
	//SortFactory factory;
	//Comparator* cmp = factory.create(order);
	movieVec::iterator movieVecIT;
	std::vector<Professional*>* proVector;


	movieVecIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieVecIT == Movies.end()){
		//std::cout << "Failure" << std::endl;
		return "Failure";
	}
	proVector = (*movieVecIT)->getProfessionals();
	switch (order) {
		case 1:
			// ID
			cmpID cmpID;
			std::sort(proVector->begin(), proVector->end(), cmpID);
			break;
		case 2:
			// Age
			cmpAge cmpAge;
			std::sort(proVector->begin(), proVector->end(), cmpAge);
			break;
		case 3:
			// MovieNum
			cmpMovieNum cmpMovieNum;
			std::sort(proVector->begin(), proVector->end(), cmpMovieNum);
			break;
		default:
			break;
	}
	return "Success";
}

/*
 *
 */
std::string MovieSystem::printMovieProfessionals(std::string MovieCode){
	movieVec::iterator movieVecIT;

	movieVecIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieVecIT == Movies.end()){
		return "Failure";
	}
	return (*movieVecIT)->printProfessionals();
}

/*
 *
 */
std::string MovieSystem::printMovie(std::string MovieCode){
	movieVec::iterator movieVecIT;

	movieVecIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieVecIT == Movies.end()){
		return "Failure";
	}
	return (*movieVecIT)->printMovie();
}

/*
 *
 */
void MovieSystem::mergeMovies(std::vector<std::string> movieCodes){
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
		std::cout << "Failure" << std::endl;
		return;
	}

	movie = *movieIT;
	it++;
	counter++;
	while (it != movieCodes.end()){
		movieIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(*it));
		if (movieIT == Movies.end()){
			std::cout << "Failure" << std::endl;
			return;
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
		genreToMovies.find(*auxGenreIT)->second->push_back(movie);
	}
	std::cout << "Success" << std::endl;
}

/*
 *
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
 *
 */
void MovieSystem::deleteMovie(std::string movieCode){
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
		std::cout << "Failure" << std::endl;
		return;
	}
	movie = *movieGeneralIT;
	proVector = movie->getProfessionals();
	// Delete movie from each professional
	for(proIT = proVector->begin();proIT != proVector->end(); proIT++){
		movieVector = (*proIT)->getMovies();
		movieIT = find_if(movieVector->begin(), movieVector->end(), movieCode_Equal(movieCode));
		movieVector->erase(movieIT);
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
	std::cout << "Success" << std::endl;
}

/*
 *
 */
void MovieSystem::deleteProfessional(std::string proID){
	Professional* pro;
	proVec::iterator proGeneralIT;
	proVec::iterator proIT;
	movieVec::iterator movieIT;
	movieVec* movieVector;

	proGeneralIT = find_if(Professionals.begin(), Professionals.end(), proID_Equal(proID));
	// movie not found
	if (proGeneralIT == Professionals.end()){
		std::cout << "Failure" << std::endl;
		return;
	}
	pro = *proGeneralIT;
	movieVector = pro->getMovies();
	// Delete pro from each movie
	for(movieIT = movieVector->begin();movieIT != movieVector->end(); movieIT++){
		deleteProfessionalFromMovie((*movieIT)->getCode(), proID);
	}
	// Delete the pro
	Professionals.erase(proGeneralIT);
	std::cout << "Success" << std::endl;
}

/*
 *
 */
std::string MovieSystem::deleteProfessionalFromMovie(std::string MovieCode, std::string profID){
	Movie* movie;
	movieVec::iterator movieGeneralIT;
	proVec::iterator proGeneralIT;
	proVec::iterator proIT;
	proVec* proVector;

	movieGeneralIT = find_if(Movies.begin(), Movies.end(), movieCode_Equal(MovieCode));
	// movie not found
	if (movieGeneralIT == Movies.end()){
		//std::cout << "Failure" << std::endl;
		return "Failure";
	}
	movie = *movieGeneralIT;
	proVector = movie->getProfessionals();
	proGeneralIT = find_if(proVector->begin(), proVector->end(), proID_Equal(profID));
	// pro not found
	if (proGeneralIT == proVector->end()){
		//std::cout << "Failure" << std::endl;
		return "Failure";
	}
	proVector->erase(proGeneralIT);
	//std::cout << "Success" << std::endl;
	return "Success";
}

/*
 *
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
 *
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
 *
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
				addMovie(movieCode, movieName, movieLength, movieReleaseYear, movieRating, movieDescription);
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
				addProfessional(proID, proName, proAge, proGender, proSpecDesc, proType);
				break;
			case 3:
				cin >> movieCode;
				cin >> proID;
				addProfessionalToMovie(movieCode, proID);
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
				mergeMovies(parsed);
				break;
			case 9:
				cin >> proID;
				cout << printMoviesWithProfessional(proID);
				break;
			case 10:
				cin >> movieCode;
				deleteMovie(movieCode);
				break;
			case 11:
				cin >> proID;
				deleteProfessional(proID);
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
