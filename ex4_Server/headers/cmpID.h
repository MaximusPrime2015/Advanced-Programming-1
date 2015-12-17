/*
 * cmpID.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef CMPID_H_
#define CMPID_H_
#include "professional.h"

class cmpID
{
public:
	//---------------------------------------------
	//| Action: compares two id's.
	//| Input: two id's.
	//| Returns: true if id1 is greater than id2. False otherwise.
	//---------------------------------------------
	bool operator()(const Professional* prof1, const Professional* prof2);
};


#endif /* CMPID_H_ */
