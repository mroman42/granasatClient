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
static int UNIT_VECTORS;

static void set_magnitude(int new_magnitude) {
    CATALOG = new_magnitude;
    printlog("");
    printf("(Star Tracker) Using star tracker catalog: %d\n", new_magnitude);
}

static void set_unitary_vectors(int new_vectors) {
    UNIT_VECTORS = new_vectors;
    printlog("");
    printf("(Star Tracker) Using %d unitary vectors\n", new_vectors);
}


#endif
