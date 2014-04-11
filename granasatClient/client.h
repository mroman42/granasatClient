/*
 * client.h
 * granaSAT.Client
 *
 *  Created on: Apr 11, 2014
 *      Author: mario
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>

// Constants
static int SOCKFD;

// Functions.

/**
 * Sends an integer to the server.
 */
void sendData(int x);


#endif /* CLIENT_H_ */
