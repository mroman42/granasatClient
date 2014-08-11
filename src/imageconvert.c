/**
 * imageconvert.c
 * granaSAT.Client
 *
 *  Created on: Aug 11, 2014
 *      Author: Mario Román
 */

#include <stdio.h>
#include <stdint.h>
#include <cv.h>
#include <highgui.h>

static void transform_image(char* filename_in, char* filename_out) {
    // Reads the raw image
    uint8_t image_stream[960*1280];
    FILE* raw_img = fopen(filename_in, "r");
    fread(image_stream, 1, 960*1280, raw_img);

    // Creates the OpenCV image
    IplImage* cv_image = cvCreateImage(cvSize(1280,960),8,1);
    cvSetZero(cv_image);

    int x,y;
    for (y=0 ; y < cv_image->height ; y++) {
        for (x=0; x < cv_image->width ; x++) {
            (cv_image->imageData + cv_image->widthStep*y)[x] = 
                ((uint8_t*) image_stream)[y * cv_image->width + x];
        }
    }
    
    // Saves the bmp image
    cvSaveImage(filename_out, cv_image, NULL);
}


int main(int argc, char* argv[]) {
    // Checks for the correct number of arguments
    if (argc != 3) {
        printf("Error. Invalid number of arguments\n");
        return 1;
    }

    transform_image(argv[1], argv[2]);

    return 0;
}
