/*
 * CommunicationPacket.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: max
 */

#include "CommunicationPacket.h"

CommunicationPacket::CommunicationPacket(int givenClientSock,MovieSystem* givenMS) {
	// TODO Auto-generated constructor stub
	clientSock = givenClientSock;
	ms = givenMS;
}

int CommunicationPacket::getClientSock(){
	return clientSock;
}

MovieSystem* CommunicationPacket::getMovieSystem(){
	return ms;
}

CommunicationPacket::~CommunicationPacket() {
	// TODO Auto-generated destructor stub
}

