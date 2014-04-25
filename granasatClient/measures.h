/*
 * measures.h
 *
 *  Created on: Apr 25, 2014
 *      Author: mario
 */

#ifndef MEASURES_H_
#define MEASURES_H_

const int MEASURES_SIZE = 30;
int magnetometer_measures[]  = {10,20,40,35,13, 50,20,16,35,90, 17,20,12,35,98, 43,20,10,35,78, 10,5,10,35,43, 34,35,34,23,34};
int accelerometer_measures[] = {10,20,10,35,98,10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43};

void add_magnetometer_measure (int measure) {
	int i;
	for (i=0; i<MEASURES_SIZE-1; i++) {
		magnetometer_measures[i] = magnetometer_measures[i+1];
	}
	magnetometer_measures[i] = measure;
}

#endif /* MEASURES_H_ */
