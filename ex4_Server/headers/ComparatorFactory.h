/*
 * ComparatorFactory.h
 *
 *  Created on: Dec 19, 2015
 *      Author: max
 */

#ifndef COMPARATORFACTORY_H_
#define COMPARATORFACTORY_H_
#include "Comparator.h"
#include "cmpID.h"
#include "cmpAge.h"
#include "cmpMovieNum.h"

class ComparatorFactory {
public:
	Comparator* create(int order);
};

#endif /* COMPARATORFACTORY_H_ */
