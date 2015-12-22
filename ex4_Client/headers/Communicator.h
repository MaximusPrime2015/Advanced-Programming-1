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
	/*
	 * c'tor.
	 */
	Communicator();

	/*
	 * d'tor.
	 */
	virtual ~Communicator();

	/*
	 * Action:
	 * 		sets up applicable connection.
	 * Input: None.
	 * Output: None.
	 */
	virtual void setCommunication(char * ip,int port) = 0;

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
