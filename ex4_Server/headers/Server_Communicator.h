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
	struct sockaddr_in sinClient;
	struct sockaddr_in sinServer;
	int server_sock;
	int client_sock;

public:

	Server_Communicator();


	virtual ~Server_Communicator();

	/*
	 * Action:
	 * 		sets up applicable connection.
	 * Input: None.
	 * Output: None.
	 */
	virtual void setCommunication(int port) = 0;

	/*
	 * Action:
	 * 		sends a message.
	 * Input: const char to message.
	 * Output: none.
	 */
	virtual void sendMessage(const char* message) = 0;

	/*
	 * Action:
	 * 		receives a message.
	 * Input: none.
	 * Output: string containing the message.
	 */
	virtual std::string receiveMessage() = 0;

	/*
	 * Action:
	 * 		closes sockets.
	 * Input: None.
	 * Output: None.
	 */
	void closeconnection();

};

#endif /* COMMUNICATOR_H_ */
