/*
 * client.c
 * granaSAT.Client
 *
 *  Created on: Apr 11, 2014
 *      Author: Mario Román
 */

#include "client.h"


void connect_server () {
	int sockfd, portno = 51717;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	printf("contacting %s on port %d\n", SERVER_IP, portno);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR opening socket");
		exit(-1);
	}

	if (( server = gethostbyname(SERVER_IP) ) == NULL) {
		perror("ERROR, no such host\n");
		exit(-1);
	}

	bzero( (char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
		perror("ERROR connecting to server");
		exit(-1);
	}

	printf("Connected\n");

	SOCKFD = sockfd;
	printf("Socket FD: %d\n", SOCKFD);
}


gboolean read_server (struct packet* data) {
	static int n = 0;


    unsigned char image_stream[IMAGE_SIZE];
    FILE* raw_image;
    char string[80];

	printf("Reading server...\n");

	// Temperature
    printf("\tSending temperature request...");
    sendData(REQ_TEMP);

    printf("Receiving temperature...");
    if ((read(SOCKFD, &DATA.temp.highByte,sizeof(signed char)) ) < 0)
        	perror("ERROR reading Temp.HighByte from socket");
    if ((read(SOCKFD, &DATA.temp.lowByte, sizeof(unsigned char)) ) < 0)
            perror("ERROR reading Temp.LowByte from socket");
    printf("Temperature received.\n");


    // Magnetometer
	printf("\tSending magnetometer request...");
	sendData(REQ_MAGN);

	printf("Receiving magnetometer data...");
	if ((read(SOCKFD,&DATA.magnetometer,sizeof(unsigned char[6])) ) < 0)
				perror("ERROR reading Magnetometer from socket");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*printf("Magnetometer data: %u,%u,%u,%u,%u,%u\n",
		DATA.magnetometer[0],DATA.magnetometer[1],
		DATA.magnetometer[2],DATA.magnetometer[3],
		DATA.magnetometer[4],DATA.magnetometer[5]);
		*/
	int16_t m[3];
	*m = (int16_t)(DATA.magnetometer[1] | DATA.magnetometer[0] << 8);
	*(m+1) = (int16_t)(DATA.magnetometer[5] | DATA.magnetometer[4] << 8) ;
	*(m+2) = (int16_t)(DATA.magnetometer[3] | DATA.magnetometer[2] << 8) ;

	float mag[3];
	*(mag+0) = (float) *(m+0)/M_XY_GAIN;
	*(mag+1) = (float) *(m+1)/M_XY_GAIN;
	*(mag+2) = (float) *(m+2)/M_Z_GAIN;

	printf("Magnetometer data (Gauss): X: %4.3f; Y: %4.3f; Z: %4.3f\n", 	mag[0],mag[1],mag[2]);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Accelerometer
	printf("\tSending accelerometer request...");
	sendData(REQ_ACCE);

	printf("Receiving accelerometer data...");
	if ((read(SOCKFD,&DATA.accelerometer,sizeof(unsigned char[6])) ) < 0)
					perror("ERROR reading Accelerometer from socket");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*printf("Accelerometer data: %u,%u,%u,%u,%u,%u\n",
			DATA.accelerometer[0],DATA.accelerometer[1],
			DATA.aqccelerometer[2],DATA.accelerometer[3],
			DATA.accelerometer[4],DATA.accelerometer[5]);*/

	int16_t a[3];
	*a = (int16_t)(DATA.accelerometer[0] | DATA.accelerometer[1] << 8) >> 4;
	*(a+1) = (int16_t)(DATA.accelerometer[2] | DATA.accelerometer[3] << 8) >> 4;
	*(a+2) = (int16_t)(DATA.accelerometer[4] | DATA.accelerometer[5] << 8) >> 4;

	float acc[3];
	*(acc+0) = (float) *(a+0)*A_GAIN;
	*(acc+1) = (float) *(a+1)*A_GAIN;
	*(acc+2) = (float) *(a+2)*A_GAIN;

	printf("Accelerometer data (G): X: %4.3f; Y: %4.3f; Z: %4.3f\n", 	acc[0],acc[1],acc[2]);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Image
	// Receive the image
    printf("\tSending image request...");
    sendData(REQ_IMAG);
	int num_bytes_received = getImage(image_stream);

	// Store the image in a file called image_received_n.data
	sprintf(string, "images/image_received_%d.data", n);
	raw_image = fopen(string, "w");
	fwrite(image_stream, 1, IMAGE_SIZE, raw_image);

	// Some debugging information
	printf("Iteration %d, number of bytes received:\t%d\n", n, num_bytes_received );
	n++;

	return 1;
}


void sendData(int x) {
    char buffer[32];
    int n;

    // Prints to a buffer.
    sprintf( buffer, "%d\n", x );

    // Sends to the server.
    if ((n = write(SOCKFD, buffer, strlen(buffer))) < 0 )
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
