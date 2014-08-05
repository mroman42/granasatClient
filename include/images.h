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
#include <cv.h>
//#include <highgui.h>
#include <data.h>

static uint8_t IMAGE_STREAM[960*1280];

static void write_image_to_file (char* filename) {
    FILE* raw_img = fopen(filename, "w");
    fwrite(IMAGE_STREAM, 1, 960*1280, raw_img);
}

/*
static void transform_image(char* filename) {
	IplImage* cv_image = cvCreateImage(cvSize(1280,960),8,1);
	cvSetZero(cv_image);

	int x,y;
	for (y=0 ; y < cv_image->height ; y++) {
		for (x=0; x < cv_image->width ; x++) {
			(cv_image->imageData + cv_image->widthStep*y)[x] = 
                ((uint8_t*) IMAGE_STREAM)[y * cv_image->width + x];
		}
	}
	
	cvSaveImage(filename, cv_image, NULL);
}
*/

#endif
