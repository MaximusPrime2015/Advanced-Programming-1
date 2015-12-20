/*
 * ServerUDP.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#include "ServerUDP.h"

ServerUDP::ServerUDP() {
	// TODO Auto-generated constructor stub

}

/*
 *
 */
void ServerUDP::setCommunication(int port){
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("ServerUDP: error creating socket");
	}

	memset(&this->sinServer, 0, sizeof(sinServer));
	sinServer.sin_family = AF_INET;
	sinServer.sin_addr.s_addr = INADDR_ANY;
	sinServer.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr *) &sinServer, sizeof(sinServer)) < 0) {
        perror("ServerUDP: error binding to socket");
    }
}

void ServerUDP::sendMessage(const char* message){
	int data_len = strlen(message);
	int sent_bytes = sendto(client_sock, message, data_len, 0,
			(struct sockaddr *) &this->sinServer, sizeof(this->sinServer));
	if (sent_bytes < 0) {
		perror("ServerUDP: error sending message to server");
	}
}

/*
 *
 */
std::string ServerUDP::receiveMessage(){
	unsigned int sinClient_len = sizeof(struct sockaddr_in);
	char buffer[4096];
	memset(&buffer, 0, sizeof(buffer));
	int bytes = recvfrom(client_sock, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &(sinClient), &sinClient_len);
	 if (bytes < 0) {
	        perror("ServerUDP: error reading from socket");
	    }
	return buffer;
}
