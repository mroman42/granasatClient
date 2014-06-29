/**
 * client.h
 * granaSAT.Client
 *
 *  Created on: Jun 29, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>

// Connection data
static bool CONNECTED = false;
static int  SOCKFD = 0;
static char SERVER_IP [] = "127.0.0.1";

// Functions
static bool connect_server();
static void check_connection();


static void check_connection() {
    if (!CONNECTED) {
        printf("Not connected to server. Checking connection.\n");
        CONNECTED = connect_server();
    }
}

static bool connect_server () {
    /* This code is adapted from: */
    /*   http://cs.smith.edu/dftwiki/index.php/Tutorial:_Client/Server_on_the_Raspberry_Pi */

	int sockfd;
    int portno = 51717;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	printf("Contacting %s on port %d\n", SERVER_IP, portno);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR opening socket");
		return false;
	}

	if (( server = gethostbyname(SERVER_IP) ) == NULL) {
		perror("ERROR, no such host\n");
		return false;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *)& serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR connecting to server");
		return false;
	}

	printf("Connected\n");
	printf("Socket file descriptor: %d\n", SOCKFD);
    SOCKFD = sockfd;

    return true;
}

#endif
