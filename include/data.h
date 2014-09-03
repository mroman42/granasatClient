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

#include <images.h>
#include <stdio.h>
#include <stdint.h>
#include "log.h"

#define IMAGE_FILE "images/image.bmp"
#define IMAGE_RAW  "images/image.raw"
#define IMAGE_BMP  "images/image.bmp"
static char WFOLDER_NAME[100];

// Status
static int SPEED = 0;
static int MODE = 1;

// Measures
static float MAG[3];
static float ACC[3];

// Temperatures
static int TEMP_CAMERA        = 0;
static int TEMP_GENERAL       = 0;
static int TEMP_CPU           = 0;
static int TEMP_MAGNETOMETER  = 0;

// Star Tracker
static int CATALOG = 4;
static int UNIT_VECTORS = 5;
static int PIXEL_THRESHOLD = 100;
static int ROI = 3;
static int POINTS = 1;
static float ERROR = 2.50;

// Camera
#define IMAGEBMP_SIZE 1229878
uint8_t IMAGE_STREAM [960*1280];
uint8_t IMAGEBMP_STREAM [IMAGEBMP_SIZE];
static int BRIGHTNESS = 0;
static int GAMMA = 100;
static int GAIN = 260;
static int EXPVALUE = 200;

// Horizon Sensor
static int BIN_TH = 50;
static int CANNY_TH = 100;

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
static void send_binthres();
static void send_canny();
static void send_mode();
static void send_speed();



// SETTING VARIABLES
static void set_value(int* value, int* VALUE, ltype type, char* msg, void (*send)()) {
    (*VALUE) = (*value);
    printlog(type, msg, (*value));
    if (send != NULL) (*send)();
}

// Star tracker
static void set_magnitude       (int magnitude) { set_value(&magnitude, &CATALOG,           LSTAR,    "Using star tracker catalog: %d\n",                send_magnitude);      }
static void set_unitary_vectors (int vectors)   { set_value(&vectors,   &UNIT_VECTORS,      LSTAR,    "Using %d unitary vectors\n",                      send_unitaryVectors); }
static void set_threshold       (int threshold) { set_value(&threshold, &PIXEL_THRESHOLD,   LSTAR,    "Using %d as threshold\n",                         send_threshold);      }
static void set_roi             (int roi)       { set_value(&roi,       &ROI,               LSTAR,    "Using %d as ROI\n",                               send_roi);            }
static void set_points          (int points)    { set_value(&points,    &POINTS,            LSTAR,    "Using %d points\n",                               send_points);         }
// Camera
static void set_brightness      (int bright)    { set_value(&bright,    &BRIGHTNESS,        LCAMERA,  "[Camera] Brightness changed to %d\n",             send_brightness);     }
static void set_gamma           (int gamma)     { set_value(&gamma,     &GAMMA,             LCAMERA,  "[Camera] Gamma changed to %d\n",                  send_gamma);          }
static void set_gain            (int gain)      { set_value(&gain,      &GAIN,              LCAMERA,  "[Camera] Gain changed to %d\n",                   send_gain);           }
static void set_exposure_value  (int expvalue)  { set_value(&expvalue,  &EXPVALUE,          LCAMERA,  "[Camera] Exposure value changed to %d\n",         send_expvalue);       }
// Horizon Sensor
static void set_binthres        (int binthres)  { set_value(&binthres,  &BIN_TH,            LHORIZON, "[Horizon Sensor] Binary threshold change to %d\n",send_binthres);       }
static void set_canny           (int canny)     { set_value(&canny,     &CANNY_TH,          LHORIZON, "[Horizon Sensor] Canny threshold change to %d\n", send_canny);          }
// Temperatures
static void set_general_temp    (int temp)      { set_value(&temp,      &TEMP_GENERAL,      LDATA,    "General temperature: %d\n",                       NULL); }
static void set_camera_temp     (int temp)      { set_value(&temp,      &TEMP_CAMERA,       LDATA,    "Camera temperature: %d\n",                        NULL); }
static void set_cpu_temp        (int temp)      { set_value(&temp,      &TEMP_CPU,          LDATA,    "CPU temperature: %d\n",                           NULL); }
static void set_magnet_temp     (int temp)      { set_value(&temp,      &TEMP_MAGNETOMETER, LDATA,    "CPU temperature: %d\n",                           NULL); }


static void set_error(float error) {
    ERROR = error;
    printlog(LSTAR, "Using %f as error\n", error);
    send_error();
}

static void set_magnetometer(float x, float y, float z) {
    printlog(LDATA, "Magnetometer measures:  %f,%f,%f\n", x,y,z);
    MAG[0] = x;
    MAG[1] = y;
    MAG[2] = z;
}

static void set_accelerometer(float x, float y, float z) {
    printlog(LDATA, "Accelerometer measures: %f,%f,%f\n", x,y,z);
    ACC[0] = x;
    ACC[1] = y;
    ACC[2] = z;
}

static void set_mode(int mode) {
    MODE = mode;
    printlog(LSTATUS, "Altitude determination mode changed\n");
    send_mode();
}

static void set_image() {
    static int image_number = 0;
    char buffer_filename[100];
    sprintf(buffer_filename,"%s/image%d.raw",WFOLDER_NAME,image_number);
    image_number++;

    write_image_to_file(IMAGE_RAW);
    write_image_to_file(buffer_filename);
    call_imageConvert(IMAGE_RAW, IMAGE_BMP);
}

static void set_speed(int speed) {
    SPEED = speed;
    printlog(LSTATUS, "Speed limit changed\n");
    send_speed();
}

static void set_working_folder_name() {
    time_t timer;
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(WFOLDER_NAME, 100, "log[%m/%d/%y](%H:%M:%S)", tm_info);
}

#endif
