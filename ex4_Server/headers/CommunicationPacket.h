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
	/*
	 * c'tor.
	 */
	CommunicationPacket(int client, MovieSystem* ms);

	/*
	 * Returns client socket.
	 */
	int getClientSock();

	/*
	 * Returns pointer to MovieSystem.
	 */
	MovieSystem* getMovieSystem();

	/*
	 * d'tor.
	 */
	virtual ~CommunicationPacket();
};

#endif /* COMMUNICATIONPACKET_H_ */
