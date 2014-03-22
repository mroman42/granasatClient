/*
 * main.c
 * granaSAT.Client 
 *
 *  Created on: Feb 22, 2014
 *      Author: Mario Román
 */

// Client libraries
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

// GTK GUI library
#include "gtkgui.h"

// Constants
const int ETHERNET_MAX = 1000;

void error(char *msg) {
  perror(msg);
  exit(1);
}

int main (int argc, char* argv[])
{
	// Measures
	int magnetometer_measures []  = {10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43,34,35,34,23,34};
	int accelerometer_measures [] = {10,20,10,35,98,10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43};


	////
	// Client/Server on Raspberry.
	////
	// Client
	int sockfd;
	int portno = 51717;
    struct sockaddr_in server_address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    printf("using port #%d, socket file descriptor #%d\n", portno, sockfd);

    // Server Adress
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( portno );
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
    	error("ERROR on binding");
    listen(sockfd,5);


	// GTK
	initialize_gtk (argc, argv, magnetometer_measures, accelerometer_measures);

	return 0;
}
