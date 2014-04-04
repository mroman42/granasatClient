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


// Client/Server on Raspberry
void sendData(int sockfd, int x) {
    int n;

    char buffer[32];
    sprintf( buffer, "%d\n", x );
    if ( (n = write( sockfd, buffer, strlen(buffer) ) ) < 0 )
	error( "ERROR writing to socket" );
    buffer[n] = '\0';
}

int getData(int sockfd) {
    char buffer[32];
    int n;

    if ((n = read(sockfd,buffer,31) ) < 0)
	error("ERROR reading from socket");
    buffer[n] = '\0';
    return atoi( buffer );
}

int connect_server () {
	int sockfd, portno = 51717;
	char serverIp[] = "192.168.0.100";
	struct sockaddr_in serv_addr;
	struct hostent *server;

	printf("contacting %s on port %d\n", serverIp, portno);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("ERROR opening socket");

	if (( server = gethostbyname( serverIp ) ) == NULL)
		error("ERROR, no such host\n");

	bzero( (char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	return sockfd;
}

int main (int argc, char* argv[])
{
	// Measures
	int magnetometer_measures []  = {10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43,34,35,34,23,34};
	int accelerometer_measures [] = {10,20,10,35,98,10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43};

	// Client
    int sockfd = connect_server();
    int data;
    printf("Sending 10...\n");
    sendData(sockfd,10);
    data = getData(sockfd);
    printf("got %d\n", data);
    sendData(sockfd,-2);

	// GTK
	initialize_gtk (argc, argv, magnetometer_measures, accelerometer_measures);

	// Close server
	close(sockfd);

	return 0;
}




