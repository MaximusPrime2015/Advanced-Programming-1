/*
 * ServerTCP.h
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#ifndef SERVERTCP_H_
#define SERVERTCP_H_
#include "Server_Communicator.h"
#include "movieSystem.h"
#include <pthread.h>
#include "CommunicationPacket.h"

class ServerTCP: public Server_Communicator {
private:
	MovieSystem *system;
	bool created = false;
	pthread_mutex_t lock;
public:
	ServerTCP();

	/*
	 * Action: Initializes needed components for TCP connection.
	 * Input: a port for the server to use.
	 * output: none.
	 */
	void setCommunication(int port);

	/*
	 * Action: sends a message to client.
	 * Input: a const char pointer to a message to send.
	 * output: none.
	 */
	void sendMessage(const char* message, int clientSock);

	/*
	 * Action: recieves a message from a client.
	 * Input: none.
	 * output: recieved message.
	 */
	std::string receiveMessage(int clientSock);
};

#endif /* SERVERTCP_H_ */
