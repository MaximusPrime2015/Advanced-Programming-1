/*
 * CommunicationPacket.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: max
 */

#include "CommunicationPacket.h"

/*
 * c'tor.
 */
CommunicationPacket::CommunicationPacket(int givenClientSock,MovieSystem* givenMS) {
	// TODO Auto-generated constructor stub
	clientSock = givenClientSock;
	ms = givenMS;
}

/*
 * returns client socket.
 */
int CommunicationPacket::getClientSock(){
	return clientSock;
}

/*
 * returns pointer to ms.
 */
MovieSystem* CommunicationPacket::getMovieSystem(){
	return ms;
}

/*
 * d'tor.
 */
CommunicationPacket::~CommunicationPacket() {
	// TODO Auto-generated destructor stub
}

