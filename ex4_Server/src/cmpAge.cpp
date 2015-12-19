/*
 * cmpAge.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#include "cmpAge.h"

/*
 * compares ages of 2 professionals.
 */
bool cmpAge::operator()(const Professional* prof1, const Professional* prof2){
	return prof1->getAge() <= prof2->getAge();
}
