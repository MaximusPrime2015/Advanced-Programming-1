/*
 * cmpAge.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef CMPAGE_H_
#define CMPAGE_H_
#include "Comparator.h"

class cmpAge : public Comparator
{
public:
	//---------------------------------------------
	//| Action: compares two ages.
	//| Input: two professionals.
	//| Returns: true if age1 is greater than age2. False otherwise.
	//---------------------------------------------
	bool operator()(const Professional* prof1, const Professional* prof2);
};

#endif /* CMPAGE_H_ */
