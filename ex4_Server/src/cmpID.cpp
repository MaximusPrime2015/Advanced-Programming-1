/*
 * cmpID.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "cmpID.h"

/*
 * compares IDs of 2 professionals.
 */
bool cmpID::operator()(const Professional* prof1, const Professional* prof2){
	return prof1->getID() <= prof2->getID();
}

Comparator::~Comparator(){}
