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
#include "packet.h"

// Constants
static int SOCKFD;
extern const int IMAGE_SIZE;
extern struct packet DATA;

// Functions.

/**
 * Sends an integer to the server.
 */
void sendData(int x);

/**
 * Reads the image from the server.
 * @param image_data Image stream.
 * @return Total bytes received.
 */
int getImage(unsigned char* image_data);

/**
 * Connects to the server.
 * @return Socket file descriptor.
 */
int connect_server ();

/**
 * Reads data from the server.
 */
void read_server (struct packet* data);


#endif /* CLIENT_H_ */
