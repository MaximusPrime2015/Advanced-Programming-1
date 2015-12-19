/*
 * ComparatorWrapper.cpp
 *
 *  Created on: Dec 19, 2015
 *      Author: max
 */

#include "ComparatorWrapper.h"

ComparatorWrapper::ComparatorWrapper(Comparator* givenCmp){
	cmp = givenCmp;
}

bool ComparatorWrapper::operator()(const Professional* prof1, const Professional* prof2){
	return cmp->operator()(prof1,prof2);
}

