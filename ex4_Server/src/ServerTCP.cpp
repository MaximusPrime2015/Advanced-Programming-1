/*
 * ServerTCP.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#include "ServerTCP.h"

/*
 *
 */
ServerTCP::ServerTCP() {
	// TODO Auto-generated constructor stub

}

/*
 *
 */
void ServerTCP::setCommunication(int port){
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		perror("ServerTCP: error creating socket");
	}
	memset(&sinServer, 0, sizeof(&sinServer));
	sinServer.sin_family = AF_INET;
	sinServer.sin_addr.s_addr = INADDR_ANY;
	sinServer.sin_port = htons(port);

	if(bind(server_sock, (struct sockaddr *) &sinServer, sizeof(sinServer)) < 0){
		perror("ServerTCP: error binding socket");
	}
	// only 1 client at a time
	if(listen(server_sock, 1) < 0){
		perror("ServerTCP: error listening to a socket");
	}
	unsigned int addr_len = sizeof(sinClient);
	client_sock = accept(server_sock, (struct sockaddr *)&sinClient, &addr_len);

	if(client_sock < 0){
		perror("ServerTCP: error accepting client");
	}
}

/*
 *
 */
void ServerTCP::sendMessage(const char* message){
	int data_len = strlen(message);

	int send_message = send(client_sock, message, data_len,0);
	if (send_message < 0) {
		perror("ServerTCP: error sending message to client");
	}
}

/*
 *
 */
std::string ServerTCP::receiveMessage(){
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));

	int expected_data_len = sizeof(buffer);
	int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

	if (read_bytes == 0) {
		perror("ServerTCP: lost connection");
	} else if (read_bytes < 0) {
		perror("ServerTCP: error getting message from server");
	} else {
		return buffer;
	}
	return "";
}
