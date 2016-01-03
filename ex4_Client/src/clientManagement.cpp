/*
 * clientManagement.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#include "clientManagement.h"
#include "clientUDP.h"
#include "clientTCP.h"
#define EXIT "-1"

/*
 * c'tor.
 * initializes client_cmt to applicable type.
 */
client_Management::client_Management(int type, int port, char *ip) {
	if (type == 0) {
		client_cmt = new client_UDP();
	} else if (type == 1) {
		client_cmt = new client_TCP();
	}

	client_cmt->setCommunication(ip, port);
}

/*
 * d'tor.
 */
client_Management::~client_Management() {
	delete this->client_cmt;
}

/*
 * gets a command from console, sends it to server, and prints out received response.
 */
void client_Management::startCommunication() {
	string input,choice, output;
	const char *message;
	const char *buffer;
	do {
		cin >> choice;
		getline(cin,input);
		input = choice + input;
		message = input.c_str();
		client_cmt->sendMessage(message);
		output = client_cmt->receiveMessage();
		if(output != EXIT){
			buffer = output.c_str();
			cout << buffer;
		}
	}while (choice != EXIT);

	client_cmt->closeconnection();
}

