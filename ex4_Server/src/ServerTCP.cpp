/*
 * ServerTCP.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: max
 */

#include "ServerTCP.h"
#define EXIT "-1"
MovieSystem* ServerTCP::system = NULL;

/*
 * Action: Receives a message from client, sends it to start() function for processing, and sends start()'s output to client.
 * Input: CommunicationPacket.
 * output: none.
 */
static void* startCommunication(void* pak);

/*
 *
 */
ServerTCP::ServerTCP() {
	// TODO Auto-generated constructor stub
	created = false;
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		perror("Error with init the mutex lock.");
	}
}

/*
 *	Initializes needed components for TCP connection.
 */
void ServerTCP::setCommunication(int port){
	CommunicationPacket* pak;
	pthread_t t;

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
	if(listen(server_sock, 5) < 0){
		perror("ServerTCP: error listening to a socket");
	}
	while(true){
		unsigned int addr_len = sizeof(sinClient);
		client_sock = accept(server_sock, (struct sockaddr *)&sinClient, &addr_len);
		if(client_sock < 0){
			perror("ServerTCP: error accepting client");
		}

		if (!created) {
			pthread_mutex_lock(&lock);
			if (!created) {
				system = new MovieSystem();
				created = true;
			}
			pthread_mutex_unlock(&lock);
		}
		pak = new CommunicationPacket(client_sock, system);
		// create thread for client
		int status = pthread_create(&t, NULL, startCommunication, (void*)pak);

		if(status){
			// error
		}
	}
}

/*
 *	sends a message to client.
 */
void ServerTCP::sendMessage(const char* message, int clientSock){
	int send_message;
	int data_len = strlen(message);


	if (data_len == 0){
		send_message = send(clientSock, message, 1,0);
	}
	else{
		send_message = send(clientSock, message, data_len,0);
	}
	if (send_message < 0) {
		perror("ServerTCP: error sending message to client");
	}
}

/*
 *	recieves a message from client.
 */
std::string ServerTCP::receiveMessage(int clientSock){
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));

	int expected_data_len = sizeof(buffer);
	int read_bytes = recv(clientSock, buffer, expected_data_len, 0);

	if (read_bytes == 0) {
		perror("ServerTCP: lost connection");
	} else if (read_bytes < 0) {
		perror("ServerTCP: error getting message from server");
	} else {
		return buffer;
	}
	return "";
}

/*
 * Receives a communicationPacket that contains client socket and movieSystem.
 * Receives a message from client, sends it to start() function for processing,
 * and sends start()'s output to client.
 */
void* startCommunication(void* givenPak){
	std::string out;
	std::string client_In;
	const char *message;
	const char *buffer;
	ServerTCP server;
	pthread_mutex_t locker;
	CommunicationPacket* pak = (CommunicationPacket*)givenPak;

	do{
		pthread_mutex_lock(&locker);
		client_In = server.receiveMessage(pak->getClientSock());
		buffer = client_In.c_str();

		out = (pak->getMovieSystem())->start(buffer);
		message = out.c_str();

		server.sendMessage(message, pak->getClientSock());
		pthread_mutex_unlock(&locker);
	} while(client_In != EXIT);

	server.closeconnection();
}
