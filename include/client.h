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
        printlog(LCLIENT,"Not connected to server. Checking connection.\n");
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
    printlog(LCLIENT, "Disconnecting. Closing sockets.\n");
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

static void send_value (int command, int value, const char* name) {
    if (CONNECTED) {
        printlog(LCLIENT, " Sending %s: %d\n", name, value);
        send_msg(command);
        send_int(value);
        printlog(LCLIENT, " %s sent\n", name);
    } 
}


static void send_magnitude()      { send_value(MSG_SET_CATALOG, CATALOG, "Magnitude"); }
static void send_unitaryVectors() { send_value(MSG_SET_STARS, UNIT_VECTORS, "Stars"); }
static void send_threshold()      { send_value(MSG_SET_PX_THRESH, PIXEL_THRESHOLD, "Threshold"); }
static void send_roi()            { send_value(MSG_SET_ROI, ROI, "ROI"); }
static void send_points()         { send_value(MSG_SET_POINTS, POINTS, "Points"); }
static void send_gain()           { send_value(MSG_SET_GAIN, GAIN, "Gain"); }
static void send_brightness()     { send_value(MSG_SET_BRIGHTNESS, BRIGHTNESS, "Brightness"); }
static void send_gamma()          { send_value(MSG_SET_GAMMA, GAMMA, "Gamma"); }
static void send_expvalue()       { send_value(MSG_SET_EXP_VAL, EXPVALUE, "Exposure"); }
static void send_binthres()       { send_value(MSG_SET_BIN_TH, BIN_TH, "Binary threshold"); }
static void send_canny()          { send_value(MSG_SET_CANNY_TH, CANNY_TH, "Canny threshold"); }

static void send_error() {
    if (CONNECTED) {
        printlog(LCLIENT, " Sending error: %f\n", ERROR);

        send_msg(MSG_SET_ERROR);
        send_int(ERROR);

        printlog(LCLIENT, " Error sent\n");
    }
}


static void send_mode() {
    if (CONNECTED) {
        printlog(LCLIENT, " Sending altitude determination mode");
        
        switch (MODE) {
            case 1: send_msg(MSG_SET_MODE_AUTO); break;
            case 2: send_msg(MSG_SET_MODE_STAR); break;
            case 3: send_msg(MSG_SET_MODE_HORI); break;
        }
        
        printlog(LCLIENT, " Altitude determination mode sent\n");        
    }
}

static void send_speed() {
    if (CONNECTED) {
        printlog(LCLIENT, " Sending speed limit (?): %d\n", SPEED);

        send_msg(MSG_PASS);
        //send_int(SPEED);

        printlog(LCLIENT, " Speed limit sent (?)\n");
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
    send_mode();
}

// COMMANDS
static void send_shutdown() {
    if (CONNECTED) {
        send_msg(MSG_END);
        printlog(LCLIENT, " Shutdown signal sent. Disconnecting");
        disconnect_server();
    }
}

static void send_restart() {
    if (CONNECTED) {
        send_msg(MSG_RESTART);
        printlog(LCLIENT, " Restart signal sent. Disconnecting");
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

static void read_image() {
    static int n_bytes = 960*1280;
    static int bytes_sent = 0;
    int n = 0;

    if (bytes_sent < n_bytes) {
        if ((n = recv(SOCKET_BIG_DATA, IMAGE_STREAM+bytes_sent, n_bytes-bytes_sent, MSG_DONTWAIT)) < 0)  {
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

    // If the image is complete, write and transform it
    if (bytes_sent == n_bytes) {
        set_image();
    }
}

// static void read_imagebmp() {
//     static int n_bytes = IMAGEBMP_SIZE;
//     static int bytes_sent = 0;
//     int n = 0;
// 
//     if (bytes_sent < n_bytes) {
//         if ((n = recv(SOCKET_BIG_DATA, IMAGEBMP_STREAM+bytes_sent, n_bytes-bytes_sent, MSG_DONTWAIT)) < 0)  {
//             if (errno != EAGAIN) {
//                 perror("ERROR reading socket");
//                 disconnect_server();
//                 return;
//             }
//             else {
//                 //printf("Non-blocking reading\n");
//             }
//         }
//         else
//             bytes_sent += n;
//     }
// 
//     // If the image is complete, write and transform it
//     if (bytes_sent == n_bytes) {
//         set_imagebmp();
//     }
// }



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

    printlog(LCLIENT,"Socket connected. File descriptor: %d\n", sockfd);
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
    printlog(LCLIENT,"Contacting %s on ports %d,%d,%d\n", SERVER_IP, PORT_COMMANDS,PORT_BIG_DATA,PORT_SMALL_DATA);

    SOCKFD1 = connect_socket(PORT_COMMANDS);
    SOCKFD2 = connect_socket(PORT_BIG_DATA);
    SOCKFD3 = connect_socket(PORT_SMALL_DATA);
    connected = SOCKFD1 && SOCKFD2 && SOCKFD3;

    if (connected) printlog(LCLIENT,"Connected\n");

    return connected;
}




#endif
