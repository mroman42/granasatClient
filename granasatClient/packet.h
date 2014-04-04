/*
 * packet.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Mario Román
 */

#ifndef PACKET_H_
#define PACKET_H_

struct temperature {
	signed char highByte;
	unsigned char lowByte;
};

struct packet {
    struct temperature temp;
    unsigned char magnetometer[6];
    unsigned char accelerometer[6];
};

#endif /* PACKET_H_ */
