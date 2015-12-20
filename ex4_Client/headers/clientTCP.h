/*
 * clientTCP.h
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#ifndef CLIENTTCP_H_
#define CLIENTTCP_H_
#include "Communicator.h"
using namespace std;
class client_TCP: public Communicator {
public:
	client_TCP();
	virtual ~client_TCP();
	void setCommunication(char * ip,int port);
	void sendMessage(const char* message);
	string receiveMessage();
};

#endif /* CLIENTTCP_H_ */
