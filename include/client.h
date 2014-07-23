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
#include "log.h"


// Connection data
static bool CONNECTED = false;
static int  SOCKFD1 = 0;
static int  SOCKFD2 = 0;
static int  SOCKFD3 = 0;
static char SERVER_IP [] = "127.0.0.1";

// Functions
static bool connect_server();
static void check_connection();


static void check_connection() {
    if (!CONNECTED) {
        printlog("Not connected to server. Checking connection.\n");
        CONNECTED = connect_server();
    }
}

static bool connect_server () {
    /* This code is adapted from: */
    /*   http://cs.smith.edu/dftwiki/index.php/Tutorial:_Client/Server_on_the_Raspberry_Pi */

	int sockfd1;
    int sockfd2;
    int sockfd3;
    int portno1 = 51717;
    int portno2 = 51718;
    int portno3 = 51719;
	struct sockaddr_in serv_addr;
	struct hostent *server;

    printlog("");
	printf("Contacting %s on ports %d,%d,%d\n", SERVER_IP, portno1,portno2,portno3);

	if ((sockfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR opening socket");
		return false;
	}

    if ((sockfd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");
        return false;
    }

    if ((sockfd3 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

	serv_addr.sin_port = htons(portno1);
	if (connect(sockfd1, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR connecting to server");
		return false;
	}

    serv_addr.sin_port = htons(portno2);
    if (connect(sockfd1, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting to server");
        return false;
    }

    serv_addr.sin_port = htons(portno3);
    if (connect(sockfd1, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting to server");
        return false;
    }


	printf("Connected\n");
	printf("Socket file descriptor 1: %d\n", SOCKFD1);
    printf("Socket file descriptor 2: %d\n", SOCKFD2);
    printf("Socket file descriptor 3: %d\n", SOCKFD3);
    SOCKFD1 = sockfd1;
    SOCKFD2 = sockfd2;
    SOCKFD3 = sockfd3;

    return true;
}

#endif
