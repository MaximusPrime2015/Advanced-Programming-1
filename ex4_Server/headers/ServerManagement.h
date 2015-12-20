/*
 * ServerManagement.h
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#ifndef SERVERMANAGEMENT_H_
#define SERVERMANAGEMENT_H_
#include "Server_Communicator.h"
#include "ServerUDP.h"
#include "ServerTCP.h"
#include "movieSystem.h"

class ServerManagement {
private:
	MovieSystem *system;
	Server_Communicator *server_cmt;
public:
	ServerManagement(int type, int port);
	void startCommunication();
	~ServerManagement();
};

#endif /* SERVERMANAGEMENT_H_ */
