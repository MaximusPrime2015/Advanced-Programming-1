/*
 * clientManagement.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: shalev
 */

#include "clientManagement.h"
#include "clientUDP.h"
#include "clientTCP.h"
client_Management::client_Management(int type, int port, char *ip) {
	if (type == 1) {
		this->client_cmt = new client_UDP();
	} else if (type == 0) {
		this->client_cmt = new client_TCP();
	}

	this->client_cmt->setCommunication(ip, port);
}

client_Management::~client_Management() {
	delete this->client_cmt;
}

void client_Management::startCommunication() {
	string EXIT = "-1";
	string input,choice;
	const char *message;
	const char *buffer;
	do {
		cin >> choice;
		getline(cin,input);
		input = input + choice;
		message = input.c_str();
		this->client_cmt->sendMessage(message);
		buffer = this->client_cmt->receiveMessage().c_str();
		cout << buffer << endl;

	}while (choice != EXIT);
	this->client_cmt->closeconnection();
}

