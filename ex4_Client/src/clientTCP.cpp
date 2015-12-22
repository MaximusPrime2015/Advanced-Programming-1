/*
 * clientTCP.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#include "clientTCP.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

client_TCP::client_TCP() {
}

client_TCP::~client_TCP() {
}

/*
 *	Initializes needed components for TCP connection.
 */
void client_TCP::setCommunication(char * ip, int port) {
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("error creating socket");
	}

	memset(&this->sinComu,0,sizeof(this->sinComu));
	this->sinComu.sin_family = AF_INET;
	this->sinComu.sin_addr.s_addr = inet_addr(ip);
	this->sinComu.sin_port = htons(port);

	if (connect(this->sock, (struct sockaddr *) &(this->sinComu),
			sizeof(this->sinComu)) < 0) {
		perror("error connecting to server");
	}
}

/*
 * sends a message to server.
 */
void client_TCP::sendMessage(const char* message){
	int data_len = strlen(message);
	int send_message = send(this->sock,message,data_len,0);
	if (send_message < 0) {
		perror("error sending message to server");
	}
}

/*
 * receives a message from server.
 */
string client_TCP::receiveMessage() {
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	int expected_data_len = sizeof(buffer);
	int read_bytes = recv(this->sock, buffer, expected_data_len, 0);
	if (read_bytes == 0) {
		perror("Lost connection");
	} else if (read_bytes < 0) {
		perror("error getting message from server");
	} else {
		return buffer;
	}
	return "";
}

