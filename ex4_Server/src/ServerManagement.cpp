/*
 * ServerManagement.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#include "ServerManagement.h"
#define EXIT "-1"

/*
 * c'tor.
 * Creates applicable server_communicator according to given type, and initializes it.
 * Initializes movieSystem.
 */
ServerManagement::ServerManagement(int type, int port) {
	if (type == 0) {
		server_cmt = new ServerUDP();
	} else if (type == 1) {
		server_cmt = new ServerTCP();
	}

	server_cmt->setCommunication(port);
}

/*
 * d'tor.
 */
ServerManagement::~ServerManagement() {
	delete system;
	delete server_cmt;
	//pthread_mutex_destroy(&lock);
}

/*
 * Recieves a message from client, sends it to start() function for processing,
 *  and sends start()'s output to client.
 */
/*
void ServerManagement::startCommunication(){
	std::string out;
	std::string client_In;
	const char *message;
	const char *buffer;

	do{
		client_In = server_cmt->receiveMessage();
		buffer = client_In.c_str();

		out = system->start(buffer);
		message = out.c_str();

		server_cmt->sendMessage(message);
	} while(client_In != EXIT);

	server_cmt->closeconnection();
}
*/
