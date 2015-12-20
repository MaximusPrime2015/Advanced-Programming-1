/*
 * main.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: max
 */
# include "movieSystem.h"

int main(){
	MovieSystem ms;
	const char* inp = "1 xyz Inception 148 2010 8.8 This is the description";
	std::cout << ms.start(inp) << std::endl;

	return 1;
}
