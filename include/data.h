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
static int ROI = 3;
static int POINTS = 1;
static float ERROR = 2.50;

// Camera
static int BRIGHTNESS = 0;
static int GAMMA = 100;
static int GAIN = 260;
static int EXPVALUE = 200;


// Sending to server
// Defined in client.h
static void send_magnitude();
static void send_threshold();
static void send_unitaryVectors();
static void send_roi();
static void send_points();
static void send_error();
static void send_roi();
static void send_brightness();
static void send_gamma();
static void send_gain();
static void send_expvalue();

// Setting variables
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

static void set_roi(int roi) {
    ROI = roi;
    printlog("");
    printf("[Star Tracker] Using %d as ROI\n", roi);
    send_roi();
}

static void set_points(int points) {
    POINTS = points;
    printlog("");
    printf("[Star Tracker] Using %d points\n", points);
    send_points();
}

static void set_error(float error) {
    ERROR = error;
    printlog("");
    printf("[Star Tracker] Using %f as error\n", error);
    send_error();
}

static void set_brightness(int bright) {
    BRIGHTNESS = bright;
    printlog("");
    printf("[Camera] Brightness changed to %d", bright);
    send_brightness();
}

static void set_gamma(int gamma) {
    GAMMA = gamma;
    printlog("");
    printf("[Camera] Gamma changed to %d", gamma);
    send_gamma();
}

static void set_gain(int gain) {
    GAIN = gain;
    printlog("");
    printf("[Camera] Gain changed to %d", gain);
    send_gain();
}

static void set_exposure_value(int expvalue) {
    EXPVALUE = expvalue;
    printlog("");
    printf("[Camera] Exposure value changed to %d", expvalue);
    send_expvalue();
}

static void set_magnetometer(float x, float y, float z) {
    printlog("");
    printf("[Data] Magnetometer measures:  %f,%f,%f\n", x,y,z);
    MAG[0] = x;
    MAG[1] = y;
    MAG[2] = z;
}

static void set_accelerometer(float x, float y, float z) {
    printlog("");
    printf("[Data] Accelerometer measures: %f,%f,%f\n", x,y,z);
    ACC[0] = x;
    ACC[1] = y;
    ACC[2] = z;
}    

#endif
