/*
 * main.cpp
 *
 *  Created on: Dec 16, 2015
 *      Author: max
 */
#include <iostream>
#include <stdlib.h>
#include "clientManagement.h"
using namespace std;

/*
 * initializes client_Management from arguments, and begins communication with server.
 */
int main(int argc, char** argv) {
	client_Management *cmt;
	int type = atoi(argv[1]);
	char *a = argv[3];
	int port = atoi(a);
	cmt = new client_Management(type,port,argv[2]);
	cmt->startCommunication();
	return 0;
}

