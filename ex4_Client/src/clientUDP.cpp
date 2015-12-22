/*
 * clientUDP.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#include "clientUDP.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

client_UDP::client_UDP() {
}

client_UDP::~client_UDP() {
}

/*
 *	Initializes needed components for UDP connection.
 */
void client_UDP::setCommunication(char * ip, int port) {
	this->sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("error creating socket");
	}
	memset(&this->sinComu, 0, sizeof(this->sinComu));
	this->sinComu.sin_family = AF_INET;
	this->sinComu.sin_addr.s_addr = inet_addr(ip);
	this->sinComu.sin_port = htons(port);
}

/*
 * sends a message to server.
 */
void client_UDP::sendMessage(const char* message) {
	int data_len = strlen(message);
	int sent_bytes = sendto(sock, message, data_len, 0,
			(struct sockaddr *) &this->sinComu, sizeof(this->sinComu));
	if (sent_bytes < 0) {
		perror("error sending message to server");
	}
}

/*
 * receives a message from server.
 */
string client_UDP::receiveMessage() {
	unsigned int from_len = sizeof(struct sockaddr_in);
	char buffer[4096];
	memset(&buffer, 0, sizeof(buffer));
	int bytes = recvfrom(this->sock, buffer, sizeof(buffer), 0,
			(struct sockaddr *) &(this->from), &from_len);
	 if (bytes < 0) {
	        perror("error reading from socket");
	    }
	return buffer;
}
