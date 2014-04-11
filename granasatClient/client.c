/*
 * client.c
 * granaSAT.Client
 *
 *  Created on: Apr 11, 2014
 *      Author: Mario Román
 */

#include "client.h"

void sendData(int x) {
    char buffer[32];
    int n;

    // Prints to a buffer.
    sprintf( buffer, "%d\n", x );

    // Sends to the server.
    if ( (n = write( SOCKFD, buffer, strlen(buffer) ) ) < 0 )
    	perror("ERROR writing to socket");

    buffer[n] = '\0';
}
