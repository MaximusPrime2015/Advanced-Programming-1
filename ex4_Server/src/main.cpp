/*
 * main.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: max
 */
# include "ServerManagement.h"
#include <iostream>
#include <stdlib.h>

/*
 * initializes ServerManagement from arguments, and begins communication with client.
 */
int main(int argc,char** argv){
	using namespace std;

	ServerManagement *sm;
	int type = atoi(argv[1]);
	int port = atoi(argv[2]);
	sm = new ServerManagement(type,port);
	//sm->startCommunication();

	delete sm;
}
