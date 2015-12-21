/*
 * main.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: max
 */
# include "ServerManagement.h"
#include <iostream>
#include <stdlib.h>

int main(int argc,char** argv){
	close(3);
	ServerManagement *sm;
	int type = atoi(argv[1]);
	int port = atoi(argv[2]);
	sm = new ServerManagement(type,port);
	sm->startCommunication();
}
