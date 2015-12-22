/*
 * Communicator.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#include "Server_Communicator.h"

Server_Communicator::Server_Communicator() {
	server_sock = -1;
	client_sock = -1;
}

Server_Communicator::~Server_Communicator() {
}
/*
 * The function closes the connection between the server and the client.
 */
void Server_Communicator::closeconnection() {
	close(client_sock);
	close(server_sock);
}
