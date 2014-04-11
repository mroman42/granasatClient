/*
 * packet.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Mario Román
 */

#ifndef PACKET_H_
#define PACKET_H_


#define REQ_TEMP		1
#define REQ_MAGN		2
#define REQ_ACCE		3
#define REQ_IMAG		4
#define CTRL_LED_ON		5
#define CTRL_LED_OFF 	6

struct temperature {
	signed char highByte;
	unsigned char lowByte;
};


struct packet {
    struct temperature temp;
    unsigned char magnetometer[6];
    unsigned char accelerometer[6];
    unsigned char image_data[1280*960];
};




#endif /* PACKET_H_ */
