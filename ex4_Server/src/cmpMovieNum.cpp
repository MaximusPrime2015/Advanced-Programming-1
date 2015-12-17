/*
 * cmpMovieNum.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "cmpMovieNum.h"

bool cmpMovieNum::operator()(const Professional* prof1, const Professional* prof2){
	return prof1->getMovieListSize() >= prof2->getMovieListSize();
}
