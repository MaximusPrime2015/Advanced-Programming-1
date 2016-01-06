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
	delete server_cmt;
}

