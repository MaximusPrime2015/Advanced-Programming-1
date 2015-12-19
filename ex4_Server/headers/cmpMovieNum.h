/*
 * cmpMovieNum.h
 *
 *  Created on: Nov 13, 2015
 *      Author: max
 */

#ifndef CMPMOVIENUM_H_
#define CMPMOVIENUM_H_
#include "Comparator.h"

class cmpMovieNum: public Comparator
{
public:
	//---------------------------------------------
	//| Action: compares two numbers represting Movie counts.
	//| Input: two Movie counts.
	//| Returns: true if mNum1 is greater than mNum2. False otherwise.
	//---------------------------------------------
	bool operator()(const Professional* prof1, const Professional* prof2);
};

#endif /* CMPMOVIENUM_H_ */
