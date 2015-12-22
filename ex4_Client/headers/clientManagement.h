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

	/*
	 * Action: c'tor.
	 * 		Creates applicable Communicator according to given type, and initializes it.
	 * Input: Type of communication, and Port to connect to, and IP of server.
	 */
	client_Management(int type,int port,char *ip);

	/*
	 * Action: d'tor
	 * 		deletes client_cmt.
	 */
	virtual ~client_Management();


	/*
	 *
	 */
	void startCommunication();
};

#endif /* CLIENTMANAGEMENT_H_ */
