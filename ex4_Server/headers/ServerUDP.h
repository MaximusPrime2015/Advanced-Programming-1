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
	void setCommunication(int port);
	void sendMessage(const char* message);
	std::string receiveMessage();
};

#endif /* SERVERUDP_H_ */
