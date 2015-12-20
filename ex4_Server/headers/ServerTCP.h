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
	void setCommunication(int port);
	void sendMessage(const char* message);
	std::string receiveMessage();
};

#endif /* SERVERTCP_H_ */
