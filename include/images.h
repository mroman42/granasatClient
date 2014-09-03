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


#define IMAGE_CONVERT "bin/imageConvert"
#define IMAGEBMP_SIZE 1229878

// Image file size constants
#define IMG_WIDTH	   1280
#define IMG_HEIGHT	   960
#define IMG_DATA_SIZE  (sizeof(uint8_t) * IMG_WIDTH * IMG_HEIGHT)
#define PARAM_SIZE	   (sizeof(int))
#define PARAM_ST_SIZE  (PARAM_SIZE * 5)
#define	IMG_FILE_SIZE  (IMG_DATA_SIZE + TIMESTAMP_SIZE + PARAM_ST_SIZE)


extern uint8_t IMAGE_STREAM [960*1280];
extern uint8_t IMAGEBMP_STREAM [IMAGEBMP_SIZE];

static void write_image_to_file (char* filename) {
    FILE* raw_img = fopen(filename, "w");
    fwrite(IMAGE_STREAM, 1, 960*1280, raw_img);
}

static void call_imageConvert (char* filename_in, char* filename_out) {
    // Forks to create a new process to run imageConvert
    char buffer[100];

    if (fork() == 0) {
        // Child process
        printlog(LIMAGE, "Calling \"imageConvert\" to convert %s into %s\n", filename_in, filename_out);
        sprintf(buffer, "%s \"%s\" \"%s\"", IMAGE_CONVERT, filename_in, filename_out);
        system(buffer);
        exit(0);
    }
}

#endif
