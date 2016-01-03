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
#include <pthread.h>
class ServerManagement {
private:
	MovieSystem *system;
	Server_Communicator *server_cmt;
	bool created = false;
	pthread_mutex_t lock;
public:

	/*
	 * Action: c'tor.
	 * 		Creates applicable server_communicator according to given type, and initializes it.
	 * 		Initializes movieSystem.
	 * Input: Type of communication, and Port for the server to use.
	 */
	ServerManagement(int type, int port);

	/*
	 * Action:
	 * 		Recieves a message from client, sends it to start() function for processing,
	 *  	and sends start()'s output to client.
	 * Input: None.
	 * Output: None.
	 */
	void startCommunication();

	/*
	 * d'tor. Deletes system, and server_cmt.
	 */
	~ServerManagement();
};

#endif /* SERVERMANAGEMENT_H_ */
