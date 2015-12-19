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
	//---------------------------------------------
	//| Action: compares two pros.
	//| Input: 2 Professional pointers.
	//| Returns: true if this; false if that.
	//---------------------------------------------
	virtual bool operator()(const Professional* prof1, const Professional* prof2) = 0;
	virtual ~Comparator();
};

#endif /* COMPARATOR_H_ */
