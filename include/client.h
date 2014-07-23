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

// Connection Ports
#define PORT_COMMANDS 51717
#define PORT_BIG_DATA 51718
#define PORT_SMALL_DATA 51719
#define SOCKET_COMMANDS SOCKFD1
#define SOCKET_BIG_DATA SOCKFD2
#define SOCKET_SMALL_DATA SOCKFD3

// Connection data
static bool CONNECTED = false;
static int  SOCKFD1 = 0;
static int  SOCKFD2 = 0;
static int  SOCKFD3 = 0;
//static char SERVER_IP [] = "127.0.0.1";
static char SERVER_IP [] = "192.168.0.200";

// Functions
static bool connect_server();
static void check_connection();

// Reading data
static void read_data_packet();


static void check_connection() {
    // It will try to connect if it is not already connected
    if (!CONNECTED) {
        printlog("Not connected to server. Checking connection.\n");
        CONNECTED = connect_server();
    }
}

static void read_data_packet() {
    uint8_t read_packet[12];
    
    if ((read(SOCKET_SMALL_DATA, read_packet, sizeof(uint8_t[12]))) < 0)
	    perror("ERROR reading packet from socket");
}

static bool connect_server () {
    /* This code is adapted from: */
    /*   http://cs.smith.edu/dftwiki/index.php/Tutorial:_Client/Server_on_the_Raspberry_Pi */

    // Using three sockets in three diferent ports
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


    // Socket 1
	if ((sockfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR opening socket");
		return false;
	}

    if ((server = gethostbyname(SERVER_IP)) == NULL) {
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

    printf("Socket file descriptor 1: %d\n", sockfd1);


    // Socket 2
    if ((sockfd2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");
        return false;
    }

    if ((server = gethostbyname(SERVER_IP)) == NULL) {
        perror("ERROR, no such host\n");
        return false;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *)& serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno2);

    if (connect(sockfd2, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting to server");
        return false;
    }

    printf("Socket file descriptor 2: %d\n", sockfd2);


    // Socket 3
    if ((sockfd3 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("ERROR opening socket");
        return false;
    }

    if ((server = gethostbyname(SERVER_IP)) == NULL) {
        perror("ERROR, no such host\n");
        return false;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *)& serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno3);

    if (connect(sockfd3, (struct sockaddr*)& serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting to server");
        return false;
    }

    printf("Socket file descriptor 3: %d\n", sockfd3);
    printf("Connected\n");

    SOCKFD1 = sockfd1;
    SOCKFD2 = sockfd2;
    SOCKFD3 = sockfd3;

    return true;
}




#endif
