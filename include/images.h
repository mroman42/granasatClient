/**
 * @file images.h
 * @author Mario Román
 * @date 5 Ago 2014
 * @brief Image management and IO. Size definitions.
 * The code in this file can write images to files,
 * transform and manage them. The image streams of
 * partial read images will be storaged here.
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
#define PARAM_SIZE	   (sizeof(uint32_t))
#define PARAM_ST_SIZE  (PARAM_SIZE * 5)
#define	IMG_FILE_SIZE  (IMG_DATA_SIZE + TIMESTAMP_SIZE + PARAM_ST_SIZE)

// Timestamp sizes
#define TV_SEC_SIZE     ( sizeof(uint32_t) )
#define TV_NSEC_SIZE    ( sizeof(uint32_t) )
#define TIMESTAMP_SIZE  ( TV_SEC_SIZE + TV_NSEC_SIZE )

extern uint8_t IMAGE_STREAM [IMG_FILE_SIZE];


/**
 * Writes the current image stream to a image file.
 * Creates a new thread to write the image.
 * @param filename Output file name
 */
static void write_image_to_file (char* filename) {
    if (fork() == 0) {
        FILE* raw_img = fopen(filename, "w");
        fwrite(IMAGE_STREAM, 1, IMG_FILE_SIZE, raw_img);
        exit(0);
    }
}


/**
 * Calls the image convert program, which converts a raw image
 * into a bmp image.
 * @param filename_in Name of the input file.
 * @param filename_out Name of the output file.
 */
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
