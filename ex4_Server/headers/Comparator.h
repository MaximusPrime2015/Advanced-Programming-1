/*
 * Comparator.h
 *
 *  Created on: Dec 19, 2015
 *      Author: max
 */

#ifndef COMPARATOR_H_
#define COMPARATOR_H_
#include "professional.h"

class Comparator {
public:
	virtual bool operator()(const Professional* prof1, const Professional* prof2) = 0;
	virtual ~Comparator();
};

#endif /* COMPARATOR_H_ */
