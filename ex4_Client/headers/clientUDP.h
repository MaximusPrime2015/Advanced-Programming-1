/*
 * clientUDP.h
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#ifndef CLIENTUDP_H_
#define CLIENTUDP_H_

#include "Communicator.h"
using namespace std;
class client_UDP: public Communicator {
public:
	client_UDP();
	virtual ~client_UDP();
	void setCommunication(char * ip,int port);
	void sendMessage(const char* message);
	string receiveMessage();
};

#endif /* CLIENTUDP_H_ */
