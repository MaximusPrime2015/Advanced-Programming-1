/*
 * ComparatorWrapper.h
 *
 *  Created on: Dec 19, 2015
 *      Author: max
 */

#ifndef COMPARATORWRAPPER_H_
#define COMPARATORWRAPPER_H_
#include "Comparator.h"

class ComparatorWrapper {
private:
	Comparator* cmp;
public:
	ComparatorWrapper(Comparator* cmp);
	bool operator()(const Professional* prof1, const Professional* prof2);
};

#endif /* COMPARATORWRAPPER_H_ */
