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
static int CATALOG;
static void set_magnitude(int new_magnitude) {
    CATALOG = new_magnitude;
    printlog("");
    printf("Using star tracker catalog: %d\n", new_magnitude);
}


#endif
