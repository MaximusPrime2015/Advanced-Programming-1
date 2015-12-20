/*
 * Communicator.h
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>


class Communicator {
protected:
	struct sockaddr_in sinComu;
	int sock;
	struct sockaddr_in from;
public:
	Communicator();
	virtual ~Communicator();
	virtual void setCommunication(char * ip,int port) = 0;
	virtual void sendMessage(const char* message) = 0;
	virtual std::string receiveMessage() = 0;
	void closeconnection();

};

#endif /* COMMUNICATOR_H_ */
