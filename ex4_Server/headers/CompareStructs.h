/*
 * CompareStructs.h
 *
 *  Created on: Dec 19, 2015
 *      Author: max
 */

#ifndef COMPARESTRUCTS_H_
#define COMPARESTRUCTS_H_
#include "movie.h"
#include "professional.h"

template <typename T>
struct pointer_values_equal{
    const T* to_find;

    bool operator()(const T* other) const
    {
        return *to_find == *other;
    }
};

struct strings_Equal{
	std::string str;
	strings_Equal(const std::string& str) : str(str) {}

    bool operator()(const std::string other) const{
		return other == str;
	}
};

struct movieCode_Equal{
	std::string code;
	movieCode_Equal(const std::string& code) : code(code) {}

    bool operator()(const Movie* movie) const{
		return movie->getCode() == code;
	}
};

struct proID_Equal{
	std::string ID;
	proID_Equal(const std::string& ID) : ID(ID) {}

    bool operator()(const Professional* pro) const{
    	return ID == pro->getID();
    }
};


#endif /* COMPARESTRUCTS_H_ */
