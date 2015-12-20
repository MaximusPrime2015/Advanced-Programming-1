/*
 * ServerManagement.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#include "ServerManagement.h"

ServerManagement::ServerManagement(int type, int port) {
	if (type == 1) {
		server_cmt = new ServerUDP();
	} else if (type == 0) {
		server_cmt = new ServerTCP();
	}

	system = new MovieSystem();
	server_cmt->setCommunication(port);
}

/*
 * d'tor.
 */
ServerManagement::~ServerManagement() {
	delete system;
	delete server_cmt;
}

void ServerManagement::startCommunication(){
	std::string EXIT = "-1";
	const char *message;
	const char *buffer;

	do{
		buffer = server_cmt->receiveMessage().c_str();
		message = system->start(buffer);
		server_cmt->sendMessage(message);
	} while(buffer != EXIT);

	server_cmt->closeconnection();
}
