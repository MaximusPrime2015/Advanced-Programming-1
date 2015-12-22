/*
 * ServerUDP.h
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#ifndef SERVERUDP_H_
#define SERVERUDP_H_
#include "Server_Communicator.h"

class ServerUDP: public Server_Communicator {
public:
	ServerUDP();
	/*
	 * Action: Initializes needed components for UDP connection.
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

#endif /* SERVERUDP_H_ */
