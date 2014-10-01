/**
 * @file client.h
 * @author Mario Román
 * @date 29 Jun 2014
 * @brief Connection. Sending and receiving data.
 * Code used to connect the client to the server and send and receive
 * data. The three sockets which are used to connect to the server
 *  are managed by the functions in this file.
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
static bool IS_SHUTDOWN_SENT = false;
static int  SOCKFD1 = 0;
static int  SOCKFD2 = 0;
static int  SOCKFD3 = 0;
//static char SERVER_IP [] = "127.0.0.1";
static char SERVER_IP [] = "192.168.0.200";

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
static void sync_time();
static void sync_time_send();
static void sync_time_rcv();
static void repeat_char();

// Variables
static int image_bytes_sent;
static int packet_bytes_sent;

/**
 * Checks the connection to the server and 
 * reconnects if it is not already connected.
 * Resends all the data if the connection is succesful.
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


/**
 * Closes all the sockets and sets the connection
 * as \e disconnected.
 */
static void disconnect_server() {
    if (CONNECTED) {
        CONNECTED = false;
        close_sockets();
        image_bytes_sent = 0;
    }
}


/**
 * Closes the three connection sockets.
 * A log message will be printed.
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


// SENDING MESSAGES

/*
* @brief Checks the connection sending a ping.
* If the connection is broken, disconnects the client.
*/
static void check_ping() {
    char zero;
    bzero(&zero,1);

    if (send(SOCKET_COMMANDS, &zero, 1, MSG_NOSIGNAL) < 0) {
        perror("ERROR sending a ping to socket");
        disconnect_server();
    } 
}

/**
 * Writes a message in the commands socket.
 * The available commands are defined in \c protocol.h.
 * @param msg Message that will be sent
 */
static void send_msg(char msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, 1) < 0) {
            perror("ERROR writing command to socket");
            disconnect_server();
            return;
        }
    }
}

/**
 * Writes an integer in the commands socket.
 * The integer can be used as an argument to a command written
 * previously.
 * @param msg Integer that will be sent
 */
static void send_int(int msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, sizeof(int)) < 0) {
            perror("ERROR writing integer to socket");
            disconnect_server();
            return;
        }
    }
}

/**
 * Writes a float in the commands socket.
 * The integer can be used as an argument to a command written
 * previously.
 * @param msg Float that will be sent
 */
static void send_float(float msg) {
    if (CONNECTED) {
        if (write(SOCKET_COMMANDS, &msg, sizeof(float)) < 0) {
            perror("ERROR writing integer to socket");
            disconnect_server();
            return;
        }
    }
}

/**
 * Sends the new value of a variable to the server.
 * All the other \b send \b functions are particular cases of this one.
 * \warning This function will do nothing if the server is not connected.
 * @param command Command used to order the value change.
 * @param value New value of the variable.
 * @param name Name of the variable, as it will appear in the log. 
 */
static void send_value (int command, int value, const char* name) {
    if (CONNECTED) {
        printlog(LCLIENT, "Sending %s: %d\n", name, value);
        send_msg(command);
        send_int(value);
        printlog(LCLIENT, "%s sent\n", name);
    } 
}


static void send_magnitude()      { send_value(MSG_SET_CATALOG,    CATALOG,         "Magnitude"        ); }
static void send_unitaryVectors() { send_value(MSG_SET_STARS,      UNIT_VECTORS,    "Stars"            ); }
static void send_threshold()      { send_value(MSG_SET_PX_THRESH,  PIXEL_THRESHOLD, "Threshold"        ); }
static void send_roi()            { send_value(MSG_SET_ROI,        ROI,             "ROI"              ); }
static void send_points()         { send_value(MSG_SET_POINTS,     POINTS,          "Points"           ); }
static void send_gain()           { send_value(MSG_SET_GAIN,       GAIN,            "Gain"             ); }
static void send_brightness()     { send_value(MSG_SET_BRIGHTNESS, BRIGHTNESS,      "Brightness"       ); }
static void send_gamma()          { send_value(MSG_SET_GAMMA,      GAMMA,           "Gamma"            ); }
static void send_expvalue()       { send_value(MSG_SET_EXP_VAL,    EXPVALUE,        "Exposure"         ); }
static void send_binthres()       { send_value(MSG_SET_BIN_TH,     BIN_TH,          "Binary threshold" ); }
static void send_canny()          { send_value(MSG_SET_CANNY_TH,   CANNY_TH,        "Canny threshold"  ); }
static void send_speed()          { send_value(MSG_SET_BANDWITH,   SPEED,           "Maximum bandwith" ); }
static void send_expmode()        { send_value(MSG_SET_EXP_MODE,   EXPMODE,         "Exposure mode"    ); }

static void send_error() {
    if (CONNECTED) {
        printlog(LCLIENT, "Sending error: %f\n", ERROR);

        send_msg(MSG_SET_ERROR);
        send_float(ERROR);

        printlog(LCLIENT, "Error sent\n");
    }
}


static void send_mode() {
    if (CONNECTED) {
        printlog(LCLIENT, "Sending altitude determination mode\n");
        
        switch (MODE) {
            case 1: send_msg(MSG_SET_MODE_AUTO); break;
            case 2: send_msg(MSG_SET_MODE_STAR); break;
            case 3: send_msg(MSG_SET_MODE_HORI); break;
        }
        
        printlog(LCLIENT, "Altitude determination mode sent\n");        
    }
}

/**
 * Sends all the variables to the server in order.
 * All the values will be updated to the server.
 * \warning This function will do nothing if the server is not connected.
 */
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
    send_speed();
}

// COMMANDS
/**
 * Sends the \c shutdown command to the server.
 * \warning This function will do nothing if the server is not connected.
 */
static void send_shutdown() {
    if (CONNECTED) {
        send_msg(MSG_END);
        printlog(LCLIENT, "Shutdown signal sent.\n");
        IS_SHUTDOWN_SENT = true;
    }
}

/**
 * Sends the \c restart command to the server.
 * \warning This function will do nothing if the server is not connected.
 */
static void send_restart() {
    if (CONNECTED) {
        send_msg(MSG_RESTART);
        printlog(LCLIENT, "Restart signal sent.\n");
    }
}

/**
 * Sends the \c start \c measurements command to the server.
 * \warning This function will do nothing if the server is not connected.
 */
static void send_start_measures() {
    if (CONNECTED) {
        send_msg(MSG_START_EXP);
        printlog(LCLIENT, "Start measures signal sent.\n");
    }
}

// READING

/**
 * Reads a command from the <tt> commands socket </tt>.
 * If the command socket is empty nothing will be read.
 * Executes the reads command.
 */
static void read_commands() {
    char command;

    // Reads a command
    if ((recv(SOCKET_COMMANDS, &command, sizeof(char), MSG_DONTWAIT)) < 0)  {
        if (errno != EAGAIN) {
            perror("ERROR reading socket");
            disconnect_server();
            return;
        }
    }
    // Executes the command
    else {
        switch (command) {
        case MSG_SYNC_TIME: sync_time_rcv(); break;
        case MSG_REPEAT: 
            if (IS_SHUTDOWN_SENT) {
                repeat_char(); 
                IS_SHUTDOWN_SENT = false;
            }
            break;
        }
    }
}

/**
 * Reads a number from the server and sends the same number. 
 */
static void repeat_char() {
    char repeat;

    // Reads a the number
    if ((recv(SOCKET_COMMANDS, &repeat, sizeof(char), 0)) < 0)  {
        perror("ERROR reading socket");
        disconnect_server();
        return;
    }

    // Sends the same number.
    send_msg(MSG_REPEAT);   
    send_msg(repeat);
}

/**
 * Currently read packet bytes.
 */
static int packet_bytes_sent = 0;

/**
 * Reads a data packet from the <tt> small data socket </tt>.
 * A data packet contains the magnetometer and accelerometer measures,
 * the temperature data and a timestamp.
 * All the read variables will be updated in the data storage.
 */
static void read_data_packet() {
    // Reading protocol
    #define A_GAIN     0.004    //[G/LSB] FS=10
    #define M_XY_GAIN  1100   	//[LSB/Gauss] GN=001
    #define M_Z_GAIN   980	    //[LSB/Gauss] GN=001
    #define T_GAIN     8	    //[LSB/ÂºC]

    #define MAG_MM_SIZE     (sizeof(uint8_t) * 6)
    #define MAG_FM_SIZE     (MAG_MM_SIZE + TIMESTAMP_SIZE)
    #define ACC_MM_SIZE     (sizeof(uint8_t) * 6)
    #define ACC_FM_SIZE     (ACC_MM_SIZE + TIMESTAMP_SIZE)

    #define TEMP_FM_SIZE	(sizeof(int32_t)*4 + TIMESTAMP_SIZE)

    #define PACKET_SIZE	    (MAG_FM_SIZE + ACC_FM_SIZE + TEMP_FM_SIZE)


    // Reading
    static int n_bytes = PACKET_SIZE;
    uint8_t packet[PACKET_SIZE];
    int n;

    if (packet_bytes_sent < n_bytes) {
        if ((n = recv(SOCKET_SMALL_DATA, packet + packet_bytes_sent, n_bytes - packet_bytes_sent, MSG_DONTWAIT)) < 0)  {
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
            packet_bytes_sent += n;
    }

    if (packet_bytes_sent == n_bytes) {
        packet_bytes_sent = 0;

        int16_t m[3];
    	*(m+0) = (int16_t)(packet[1] | packet[0] << 8);
    	*(m+1) = (int16_t)(packet[5] | packet[4] << 8);
    	*(m+2) = (int16_t)(packet[3] | packet[2] << 8);

    	float MAG[3];
    	*(MAG+0) = (float) *(m+0)/M_XY_GAIN;
    	*(MAG+1) = (float) *(m+1)/M_XY_GAIN;
    	*(MAG+2) = (float) *(m+2)/M_Z_GAIN;
        
        int16_t a[3];
        *(a+0) = (int16_t)(packet[MAG_FM_SIZE+0] | packet[MAG_FM_SIZE+1] << 8) >> 4;
        *(a+1) = (int16_t)(packet[MAG_FM_SIZE+2] | packet[MAG_FM_SIZE+3] << 8) >> 4;
        *(a+2) = (int16_t)(packet[MAG_FM_SIZE+4] | packet[MAG_FM_SIZE+5] << 8) >> 4;
   
        float ACC[3];
        *(ACC+0) = (float) *(a+0)*A_GAIN;
        *(ACC+1) = (float) *(a+1)*A_GAIN;
        *(ACC+2) = (float) *(a+2)*A_GAIN;

        int32_t temps[4];
        int offset = MAG_FM_SIZE + ACC_FM_SIZE;
        *(temps+0) = (int32_t)(packet[offset+4] | packet[offset+5] << 8 | packet[offset+6] << 16 | packet[offset+7] << 24);
        *(temps+1) = (int32_t)(packet[offset+0] | packet[offset+1] << 8 | packet[offset+2] << 16 | packet[offset+3] << 24);
        *(temps+2) = (int32_t)(packet[offset+8] | packet[offset+9] << 8 | packet[offset+10] << 16 | packet[offset+11] << 24);
        *(temps+3) = (int32_t)(packet[offset+12] | packet[offset+13] << 8 | packet[offset+14] << 16 | packet[offset+15] << 24);

        set_magnetometer(MAG[0],MAG[1],MAG[2]);
        set_accelerometer(ACC[0],ACC[1],ACC[2]);

        set_general_temp (temps[0]);
        set_camera_temp  (temps[1]);
        set_cpu_temp     (temps[3]);
        set_magnet_temp  (temps[2]);
    }
}

/**
 * Currently read image bytes.
 */
static int image_bytes_sent = 0;

/**
 * Reads an image from the <tt>big data socket<\tt>.
 * If the image is not completely sent, it reads the partial
 * image and storages it. The rest of the image will be read
 * in other call to the function.
 *
 * If the image is complete, it writes it to a file and transforms
 * it into a bmp file.
 */
static void read_image() {
    static int n_bytes = IMG_FILE_SIZE;
    int n = 0;

    if (image_bytes_sent < n_bytes) {
        if ((n = recv(SOCKET_BIG_DATA, IMAGE_STREAM+image_bytes_sent, n_bytes-image_bytes_sent, MSG_DONTWAIT)) < 0)  {
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
            image_bytes_sent += n;
    }

    // If the image is complete, write and transform it
    if (image_bytes_sent == n_bytes) {
        image_bytes_sent = 0;
        set_image();
    }
}


/**
 * Creates a socket and connects to it.
 * @param portno Port number.
 * @return The socket file descriptor.
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
        close(sockfd);
        return false;
    }

    printlog(LCLIENT,"Socket connected. File descriptor: %d\n", sockfd);
    return sockfd;
}

/**
 * Connects to the server using three sockets.
 * The complete connection to the server is done by this function.
 * It will open three sockets: a <tt>small data socket</tt>, a <tt>big data socket</tt> 
 * and a a <tt>commands socket</tt>.
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

/**
 * Exchanges synchronisation data with the server.
 * After sending the MSG_SYNC_TIME message, the client measures its own time (since Epoch)
 * and sends it.
 * After receiving the server clock measurement, the client measures its own time again
 * and logs both measurements.
 */
static void sync_time(){
    sync_time_send();

}

static void sync_time_send() {
    struct timespec TC_1;
    uint32_t timestamp_buffer[2];

    //Sending of MSG_SYNC_TIME command
    send_msg(MSG_SYNC_TIME);

    //Measurement of client timestamp 1
    clock_gettime(CLOCK_REALTIME, &TC_1);
    timestamp_buffer[0] = TC_1.tv_sec;
    timestamp_buffer[1] = TC_1.tv_nsec;

    //Sending of client timestamp 1
    int bytes_sent, n;
    bytes_sent = 0;
    while (CONNECTED && bytes_sent < TIMESTAMP_SIZE) {
        if ((n = write(SOCKET_COMMANDS, &timestamp_buffer+bytes_sent, TIMESTAMP_SIZE-bytes_sent)) < 0) {
            perror("ERROR writing integer to socket");
            disconnect_server();
            return;
        }
        else
            bytes_sent += n;
    }
}

static void sync_time_rcv() {
    struct timespec TC_2;
    uint32_t timestamp_buffer[2];

    //Reception of server timestamp 2
    int bytes_rcvd, n;
    bytes_rcvd = 0;
    while (CONNECTED && bytes_rcvd < TIMESTAMP_SIZE) {
        if ((n = recv(SOCKET_COMMANDS, &timestamp_buffer+bytes_rcvd, TIMESTAMP_SIZE-bytes_rcvd, MSG_DONTWAIT)) < 0)  {
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
            bytes_rcvd += n;
    }

    //Measurement of client timestamp 2
    clock_gettime(CLOCK_REALTIME, &TC_2);

    //Server timestamp 2 and client timestamp 2 log
    printlog(LDATA, "Synchronisation data: %u.%u\t%u.%u\n",
                    timestamp_buffer[0], timestamp_buffer[1],
                    TC_2.tv_sec, TC_2.tv_nsec);
}

#endif
