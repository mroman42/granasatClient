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

// IMAGE AND BUFFER SIZES
// Image
#define IMG_WIDTH	   1280
#define IMG_HEIGHT	   960
#define IMG_DATA_SIZE  (sizeof(uint8_t) * IMG_WIDTH * IMG_HEIGHT)
// Timestamp
#define TV_SEC_SIZE    (sizeof(uint32_t))
#define TV_NSEC_SIZE   (sizeof(uint32_t))
#define TIMESTAMP_SIZE (TV_SEC_SIZE + TV_NSEC_SIZE)
// Parameters
#define PARAM_SIZE	   (sizeof(uint32_t))
#define PARAM_ST_SIZE  (PARAM_SIZE * 5)
// Att data
#define ATT_MODE_SIZE  (sizeof(uint8_t))
#define ATT_DATA_SIZE  10*sizeof(uint32_t)
#define ATT_FILE_SIZE  ATT_MODE_SIZE + ATT_DATA_SIZE
// File
#define IMG_FILE_SIZE  (IMG_DATA_SIZE + TIMESTAMP_SIZE + PARAM_ST_SIZE + ATT_FILE_SIZE)

// RESIZED IMAGE SIZE
#define RSIMG_WIDTH     640
#define RSIMG_HEIGHT	480


// Buffers
uint8_t  image_stream[IMG_DATA_SIZE];
uint32_t timestamp_buffer[2];
uint32_t parameters_buffer[5];
uint8_t  attmode_buffer[ATT_MODE_SIZE];
uint32_t attfile_buffer[10];

/**
 * Reads the image file and stores the image data,
 * the timestamp data and the paramenters data.
 * @param filename_in Input file.
 */
static void read_image(const char* filename_in) {
    FILE* raw_img = fopen(filename_in, "r");

    // Reads image
    fread(image_stream, 1, IMG_DATA_SIZE, raw_img);
    // Reads timestamp
    fread(timestamp_buffer, 1, TIMESTAMP_SIZE, raw_img);
    // Reads parameters
    fread(parameters_buffer, 1, PARAM_ST_SIZE, raw_img);
    // Reads attitude mode
    fread(attmode_buffer, 1, ATT_MODE_SIZE, raw_img);
    // Reads attitude file
    fread(attfile_buffer, 1, ATT_DATA_SIZE, raw_img);
}

/**
 * Transforms a raw image into a resized bmp image.
 * @param filename_in Input file.
 * @param filename_out Output file.
 */
static void transform_image(const char* filename_in, const char* filename_out) {
    read_image(filename_in);

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

    // Writes star data
    CvFont font;
    CvScalar text_colour = cvScalar(255,255,255,0);
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5, 0, 1.5, 8);
    char string[100];

    //TIMESTAMP
    sprintf(string, "%u.%u", timestamp_buffer[0], timestamp_buffer[1]);
    cvPutText(cv_image, string, cvPoint(20, 20), &font, text_colour);

    //PARAMETERS
    sprintf(string, "BRIGHTNESS:%d GAMMA:%d GAIN:%d EXP_MODE:%d EXP_VALUE:%d",
            parameters_buffer[0], parameters_buffer[1], parameters_buffer[2], parameters_buffer[3], parameters_buffer[4]);
    cvPutText(cv_image, string, cvPoint(20, 40), &font, text_colour);

    //ATTITUDE DATA
    //Attitude mode
    sprintf(string, "ATTITUDE MODE: ");
    switch(attmode_buffer[0]){
        case 0:
            sprintf(string, "%s Auto", string);
            break;

        case 1:
            sprintf(string, "%s Star tracker", string);
            break;

        case 2:
            sprintf(string, "%s Horizon sensor", string);
            break;
    }
    cvPutText(cv_image, string, cvPoint(20, 60), &font, text_colour);

    //Attitude data
    int i;
    for (i = 0; i < 10; ++i)
    {
        sprintf(string, "%d", attfile_buffer[i]);
        cvPutText(cv_image, string, cvPoint(20, 80+i*20), &font, text_colour);
    }

    
    
    // Resizes and saves the bmp image
    IplImage *resized_img = cvCreateImage (cvSize(RSIMG_WIDTH,RSIMG_HEIGHT), cv_image->depth, cv_image->nChannels);
    cvResize(cv_image, resized_img, CV_INTER_LINEAR);
    cvSaveImage(filename_out, resized_img, NULL);
    cvReleaseImage(&cv_image);
    cvReleaseImage(&resized_img);
}


int main(int argc, char* argv[]) {
    // Checks for the correct number of arguments
    if (argc != 3) {
        printf("[ImageConvert] Error. Invalid number of arguments\n");
        return 1;
    }

    const char* filename_in = argv[1];
    const char* filename_out = argv[2];

    printf("[ImageConvert] Converting %s into %s\n", filename_in, filename_out);
    transform_image(filename_in, filename_out);

    return 0;
}
