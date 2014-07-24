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
#include <errno.h>
#include "log.h"
#include "protocol.h"
#include "data.h"


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
static void read_data_packet();
static void disconnect_server();
static void send_msg(char msg);
static void send_int(int msg);
static void send_all();


static void check_connection() {
    // It will try to connect if it is not already connected
    if (!CONNECTED) {
        printlog("Not connected to server. Checking connection.\n");
        CONNECTED = connect_server();
    
        if (CONNECTED) {
            send_all();
        }
    }
}

static void disconnect_server() {
    if (CONNECTED) {
        CONNECTED = false;
    }
}

static void send_msg(char msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, 1) < 0) {
            perror("ERROR writing socket");
            disconnect_server();
            return;
        }
    }
}

static void send_int(int msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, sizeof(int)) < 0) {
            perror("ERROR writing socket");
            disconnect_server();
            return;
        }
    }
}

static void send_magnitude() {
    printlog("");
    printf("[Client] Sending magnitude: %d\n", CATALOG);

    send_msg(MSG_SET_CATALOG);
    send_int(CATALOG);

    printlog("[Client] Magnitude sent\n");
}

static void send_unitaryVectors() {
    printlog("");
    printf("[Client] Sending stars: %d\n", CATALOG);

    send_msg(MSG_SET_STARS);
    send_int(UNIT_VECTORS);

    printlog("[Client] Stars sent\n");
}

static void send_all() {
    send_magnitude();
    send_unitaryVectors();
}

static void read_data_packet() {
    // Reading protocol
    #define A_GAIN     0.004    //[G/LSB] FS=10
    #define M_XY_GAIN  1100   	//[LSB/Gauss] GN=001
    #define M_Z_GAIN   980	    //[LSB/Gauss] GN=001
    #define T_GAIN     8	    //[LSB/ºC]
    static int n_bytes = 12;
    static int bytes_sent = 0;
    uint8_t packet[12];
    int n;

    if (bytes_sent < n_bytes) {
        if ((n = recv(SOCKET_SMALL_DATA, packet + bytes_sent, n_bytes - bytes_sent, MSG_DONTWAIT)) < 0)  {
            if (errno != EAGAIN) {
                perror("ERROR reading socket");
                disconnect_server();
                return;
            }
            else {
                //printf("Non-blocking reading\n");
            }
        }
        else
            bytes_sent += n;
    }

    if (bytes_sent == n_bytes) {
        bytes_sent = 0;

        int16_t m[3];
	    *(m+0) = (int16_t)(packet[1] | packet[0] << 8);
	    *(m+1) = (int16_t)(packet[5] | packet[4] << 8);
	    *(m+2) = (int16_t)(packet[3] | packet[2] << 8);
	    *(m+0) = (float) *(m+0)/M_XY_GAIN;
	    *(m+1) = (float) *(m+1)/M_XY_GAIN;
	    *(m+2) = (float) *(m+2)/M_Z_GAIN;
        
        int16_t a[3];
        *(a+0) = (int16_t)(packet[6] | packet[7] << 8) >> 4;
        *(a+1) = (int16_t)(packet[8] | packet[9] << 8) >> 4;
        *(a+2) = (int16_t)(packet[10] | packet[11] << 8) >> 4;
        *(a+0) = (float) *(a+0)*A_GAIN;
        *(a+1) = (float) *(a+1)*A_GAIN;
        *(a+2) = (float) *(a+2)*A_GAIN;

        set_magnetometer(m[0],m[1],m[2]);
        set_accelerometer(a[0],a[1],a[2]);
    }
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
