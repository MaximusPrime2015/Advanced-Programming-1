/*
 * Communicator.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#include "Communicator.h"

Communicator::Communicator() {sock = -1;}

Communicator::~Communicator() {}
/*The function close the connection between the server and the client.*/
void Communicator::closeconnection() {
	close(this->sock);
}
