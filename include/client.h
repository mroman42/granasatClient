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


// Connection Sockets

#define SOCKET_COMMANDS   SOCKFD1
#define SOCKET_BIG_DATA   SOCKFD2
#define SOCKET_SMALL_DATA SOCKFD3

// Connection data
static bool CONNECTED = false;
static int  SOCKFD1 = 0;
static int  SOCKFD2 = 0;
static int  SOCKFD3 = 0;
static char SERVER_IP [] = "127.0.0.1";
//static char SERVER_IP [] = "192.168.0.200";

// Functions
static bool connect_server();
static void check_connection();
static void check_ping();
static void read_data_packet();
static void disconnect_server();
static void close_sockets();
static void send_msg(char msg);
static void send_int(int msg);
static void send_all();


/*
    Checks the connection to the server and 
    reconnects if it is not already connected.
    Resends all the data if the connection is succesful.
*/
static void check_connection() {
    check_ping();

    if (!CONNECTED) {
        printlog("Not connected to server. Checking connection.\n");
        CONNECTED = connect_server();
    
        if (CONNECTED)
            send_all();
    }
}

/*
    Closes all the sockets and sets the connection
    as 'disconnected'.
 */
static void disconnect_server() {
    if (CONNECTED) {
        CONNECTED = false;
        close_sockets();
    }
}

/*
    Closes the three sockets.
 */
static void close_sockets() {
    printlog("Disconnecting. Closing sockets.\n");
    close(SOCKFD1);
    close(SOCKFD2);  
    close(SOCKFD3);
    SOCKFD1 = 0;
    SOCKFD2 = 0;
    SOCKFD3 = 0;
}


/**
 *   SENDING MESSAGES
 */
static void check_ping() {
    char zero;
    bzero(&zero,1);

    if (send(SOCKET_COMMANDS, &zero, 1, MSG_NOSIGNAL) < 0) {
        perror("ERROR sending a ping to socket");
        disconnect_server();
    } 
}

static void send_msg(char msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, 1) < 0) {
            perror("ERROR writing command to socket");
            disconnect_server();
            return;
        }
    }
}

static void send_int(int msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, sizeof(int)) < 0) {
            perror("ERROR writing integer to socket");
            disconnect_server();
            return;
        }
    }
}

static void send_magnitude() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending magnitude: %d\n", CATALOG);

        send_msg(MSG_SET_CATALOG);
        send_int(CATALOG);

        printlog("[Client] Magnitude sent\n");
    }
}

static void send_unitaryVectors() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending stars: %d\n", UNIT_VECTORS);

        send_msg(MSG_SET_STARS);
        send_int(UNIT_VECTORS);

        printlog("[Client] Stars sent\n");
    }
}

static void send_threshold() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending threshold: %d\n", PIXEL_THRESHOLD);

        send_msg(MSG_SET_PX_THRESH);
        send_int(PIXEL_THRESHOLD);

        printlog("[Client] Threshold sent\n");
    }
}

static void send_roi() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending ROI: %d\n", ROI);

        send_msg(MSG_SET_ROI);
        send_int(ROI);

        printlog("[Client] ROI sent\n");
    }
}

static void send_points() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending points: %d\n", POINTS);

        send_msg(MSG_SET_POINTS);
        send_int(POINTS);

        printlog("[Client] Points sent\n");
    }
}

static void send_gain() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending gain: %d\n", GAIN);

        send_msg(MSG_SET_GAIN);
        send_int(GAIN);

        printlog("[Client] Gain sent\n");
    }
}

static void send_error() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending error: %f\n", ERROR);

        send_msg(MSG_SET_ERROR);
        send_int(ERROR);

        printlog("[Client] Error sent\n");
    }
}


static void send_brightness() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending brightness: %d\n", BRIGHTNESS);

        send_msg(MSG_SET_BRIGHTNESS);
        send_int(BRIGHTNESS);

        printlog("[Client] Brightness sent\n");
    }
}

static void send_gamma() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending gamma: %d\n", GAMMA);

        send_msg(MSG_SET_GAMMA);
        send_int(GAMMA);

        printlog("[Client] Gamma sent\n");
    }
}

static void send_expvalue() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending exposure value: %d\n", EXPVALUE);

        send_msg(MSG_SET_EXP_VAL);
        send_int(EXPVALUE);

        printlog("[Client] Exposure value sent\n");
    }
}

static void send_binthres() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending binary threshold: %d\n", BIN_TH);

        send_msg(MSG_SET_BIN_TH);
        send_int(BIN_TH);

        printlog("[Client] Binary threshold sent\n");
    }
}

static void send_canny() {
    if (CONNECTED) {
        printlog("");
        printf("[Client] Sending canny threshold: %d\n", CANNY_TH);

        send_msg(MSG_SET_CANNY_TH);
        send_int(CANNY_TH);

        printlog("[Client] Canny threshold sent\n");
    }
}

static void send_all() {
    send_magnitude();
    send_unitaryVectors();
    send_threshold();
    send_brightness();
    send_gamma();
    send_expvalue();
    send_binthres();
    send_canny();
}

// COMMANDS
static void send_shutdown() {
    if (CONNECTED) {
        send_msg(MSG_END);
        printlog("[Client] Shutdown signal sent. Disconnecting");
        disconnect_server();
    }
}

static void send_restart() {
    if (CONNECTED) {
        send_msg(MSG_RESTART);
        printlog("[Client] Restart signal sent. Disconnecting");
        disconnect_server();
    }
}

// READING
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

/*
    Creates a socket and connects to it.
    Parameters:
        portno - Port number
    Returns:
        the socket file descriptor
 */
static int connect_socket(int portno) {
    int sockfd;
    struct hostent *server;
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting to server");
        return false;
    }

    printlog("");
    printf("Socket connected. File descriptor: %d\n", sockfd);
    return sockfd;
}

/*
    Connects to the server using three sockets.
 */
static bool connect_server () {
    /* This code is adapted from: */
    /*   http://cs.smith.edu/dftwiki/index.php/Tutorial:_Client/Server_on_the_Raspberry_Pi */
    disconnect_server();
    bool connected = false;

    // Using three sockets in three diferent ports
    printlog("");
	printf("Contacting %s on ports %d,%d,%d\n", SERVER_IP, PORT_COMMANDS,PORT_BIG_DATA,PORT_SMALL_DATA);

    SOCKFD1 = connect_socket(PORT_COMMANDS);
    SOCKFD2 = connect_socket(PORT_BIG_DATA);
    SOCKFD3 = connect_socket(PORT_SMALL_DATA);
    connected = SOCKFD1 && SOCKFD2 && SOCKFD3;

    if (connected) printlog("Connected\n");

    return connected;
}




#endif
