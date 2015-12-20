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
#include <string.h>


class Server_Communicator {
protected:
	struct sockaddr_in sinServer;
	int server_sock;
	int client_sock;
	struct sockaddr_in sinClient;
public:
	Server_Communicator();
	virtual ~Server_Communicator();
	virtual void setCommunication(int port) = 0;
	virtual void sendMessage(const char* message) = 0;
	virtual std::string receiveMessage() = 0;
	void closeconnection();

};

#endif /* COMMUNICATOR_H_ */
