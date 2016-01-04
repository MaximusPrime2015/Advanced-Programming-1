/*
 * CommunicationPacket.h
 *
 *  Created on: Jan 4, 2016
 *      Author: max
 */

#ifndef COMMUNICATIONPACKET_H_
#define COMMUNICATIONPACKET_H_

class MovieSystem;

class CommunicationPacket {
private:
	int clientSock;
	MovieSystem *ms;
public:
	CommunicationPacket(int client, MovieSystem* ms);
	int getClientSock();
	MovieSystem* getMovieSystem();
	virtual ~CommunicationPacket();
};

#endif /* COMMUNICATIONPACKET_H_ */
