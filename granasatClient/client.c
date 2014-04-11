/*
 * client.c
 * granaSAT.Client
 *
 *  Created on: Apr 11, 2014
 *      Author: Mario Román
 */

#include "client.h"


int connect_server () {
	int sockfd, portno = 51717;
	//char serverIp[] = "192.168.0.100"; // Raspberry IP
	char serverIp[] = "127.0.0.1";
	struct sockaddr_in serv_addr;
	struct hostent *server;

	printf("contacting %s on port %d\n", serverIp, portno);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("ERROR opening socket");

	if (( server = gethostbyname( serverIp ) ) == NULL)
		error("ERROR, no such host\n");

	bzero( (char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	printf("Connected\n");

	return sockfd;
}


void read_server (struct packet* data) {
	static int n = 0;

    unsigned char image_stream[IMAGE_SIZE];
    FILE* raw_image;
    char string[80];

	// Temperature
    sendData(REQ_TEMP);
    if ((read(SOCKFD,(char*) DATA.temp.highByte,sizeof(unsigned char)) ) < 0)
        	error("ERROR reading Temp.HighByte from socket");
    if ((read(SOCKFD,(char*) DATA.temp.lowByte,sizeof(unsigned char)) ) < 0)
            error("ERROR reading Temp.LowByte from socket");

    // Magnetometer
    sendData(REQ_MAGN);
    if ((read(SOCKFD,(char*) DATA.magnetometer,sizeof(unsigned char[6])) ) < 0)
            	error("ERROR reading Magnetometer from socket");

    // Accelerometer
    sendData(REQ_ACCE);
    if ((read(SOCKFD,(char*) DATA.accelerometer,sizeof(unsigned char[6])) ) < 0)
                	error("ERROR reading Accelerometer from socket");

	// Image
	// Receive the image
    sendData(REQ_IMAG);
	int num_bytes_received = getImage(image_stream);

	// Store the image in a file called image_received_n.data
	sprintf(string, "images/image_received_%d.data", n);
	raw_image = fopen(string, "w");
	fwrite(image_stream, 1, IMAGE_SIZE, raw_image);

	// Some debugging information
	printf("Iteration %d, number of bytes received:\t%d\n", n, num_bytes_received );
	n++;
}


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


int getImage(unsigned char* image_data) {
	const int total_bytes = IMAGE_SIZE;
	int bytes_received = 0;
	int n;

	// Reads until the total image is received.
	while(bytes_received < total_bytes){
		if ( (n = read(SOCKFD,image_data+bytes_received,total_bytes-bytes_received) ) < 0 ){
			perror( ( "ERROR reading from socket") );
			break;
		}
		else
			bytes_received += n;
	}

	return bytes_received;
}
