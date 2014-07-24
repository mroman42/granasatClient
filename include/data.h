/**
 * data.h
 * granaSAT.Client
 *
 *  Created on: Jun 24, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef DATA_H
#define DATA_H

#include "log.h"

// Measures
static float MAG[3];
static float ACC[3];

// Star Tracker
static int CATALOG = 4;
static int UNIT_VECTORS = 5;
static int PIXEL_THRESHOLD = 100;

// Sending to server
// Defined in client.h
static void send_magnitude();
static void send_threshold();
static void send_unitaryVectors();


static void set_magnitude(int new_magnitude) {
    CATALOG = new_magnitude;
    printlog("");
    printf("[Star Tracker] Using star tracker catalog: %d\n", new_magnitude);
    send_magnitude();
}

static void set_unitary_vectors(int new_vectors) {
    UNIT_VECTORS = new_vectors;
    printlog("");
    printf("[Star Tracker] Using %d unitary vectors\n", new_vectors);
    send_unitaryVectors();
}

static void set_threshold(int threshold) {
    PIXEL_THRESHOLD = threshold;
    printlog("");
    printf("[Star Tracker] Using %d as threshold\n", threshold);
    send_threshold();
}

static void set_magnetometer(float x, float y, float z) {
    MAG[0] = x;
    MAG[1] = y;
    MAG[2] = z;
}

static void set_accelerometer(float x, float y, float z) {
    ACC[0] = x;
    ACC[1] = y;
    ACC[2] = z;
}    

#endif
