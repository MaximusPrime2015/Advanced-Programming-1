/*
 * ServerTCP.h
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#ifndef SERVERTCP_H_
#define SERVERTCP_H_
#include "Server_Communicator.h"

class ServerTCP: public Server_Communicator {
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
	void sendMessage(const char* message);

	/*
	 * Action: recieves a message from a client.
	 * Input: none.
	 * output: recieved message.
	 */
	std::string receiveMessage();
};

#endif /* SERVERTCP_H_ */
