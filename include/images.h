/**
 * images.h
 * granaSAT.Client
 *
 *  Created on: Ago 5, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef IMAGES_H_
#define IMAGES_H_

#include <stdio.h>
#include <stdint.h>
#include "data.h"
#include "log.h"


#define IMAGEBMP_SIZE 1229878
extern uint8_t IMAGE_STREAM [960*1280];
extern uint8_t IMAGEBMP_STREAM [IMAGEBMP_SIZE];

static void write_image_to_file (char* filename) {
    FILE* raw_img = fopen(filename, "w");
    fwrite(IMAGE_STREAM, 1, 960*1280, raw_img);
}

// static void write_bmp_to_file (char* filename) {
//     FILE* raw_img = fopen(filename, "w");
//     fwrite(IMAGEBMP_STREAM, 1, IMAGEBMP_SIZE, raw_img);
// }

static void call_imageConvert (char* filename_in, char* filename_out) {
    // Forks to create a new process to run imageConvert
    char buffer[100];

    if (fork() == 0) {
        // Child process
        printlog(LIMAGE, "Calling \"imageConvert\" to convert %s into %s", filename_in, filename_out);
        sprintf(buffer, "imageConvert \"%s\" \"%s\"", filename_in, filename_out);
        system(buffer);
        exit(0);
    }
}

#endif
