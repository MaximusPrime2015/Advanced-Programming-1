/*
 * ComparatorFactory.cpp
 *
 *  Created on: Dec 19, 2015
 *      Author: max
 */

#include "ComparatorFactory.h"

Comparator* ComparatorFactory::create(int order){
	switch (order) {
		case 1:
			// ID
			return new cmpID;
		case 2:
			// Age
			return new cmpAge;
		case 3:
			// MovieNum
			return new cmpMovieNum;
		default:
			return new cmpID;
	}
}
