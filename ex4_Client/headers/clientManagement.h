/*
 * clientManagement.h
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#ifndef CLIENTMANAGEMENT_H_
#define CLIENTMANAGEMENT_H_
#include "Communicator.h"
#include <iostream>
class client_Management {
private:
	Communicator *client_cmt;
public:
	client_Management(int type,int port,char *ip);
	virtual ~client_Management();
	void startCommunication();
};

#endif /* CLIENTMANAGEMENT_H_ */
