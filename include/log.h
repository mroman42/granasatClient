/**
 * @file log.h
 * @author Mario Román
 * @date 11 Jul 2014
 * @brief Log writing.
 */

// Avoids redefinition
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <time.h>
#include "colours.h"

typedef enum {LSTATUS,LCLIENT,LDATA,LIMAGE,LCAMERA,LSTAR,LHORIZON} ltype;
static void printlog(ltype msgtype, const char* msg, ...);
static void printtime();


/**
 * Prints the current time and the message in a coloured log.
 * @param msgtype Type of the message.
 * @param format Message format.
 */
static void printlog(ltype msgtype, const char* format, ...) {
    va_list args;
    va_start(args, format);
    printtime();
    
    char colour[20];
    char identf[20];
    switch (msgtype) {
        case LSTATUS: sprintf(colour, KWHT); sprintf(identf, "Status"); break;
        case LCLIENT: sprintf(colour, KGRN); sprintf(identf, "Client"); break;
        case LDATA:   sprintf(colour, KBLU); sprintf(identf, "Data"); break;
        case LIMAGE:  sprintf(colour, KMAG); sprintf(identf, "Image"); break;
        case LCAMERA: sprintf(colour, KCYN); sprintf(identf, "Camera"); break;
        case LSTAR:   sprintf(colour, KYEL); sprintf(identf, "Star Tracker"); break;
        case LHORIZON:sprintf(colour, KLRE); sprintf(identf, "Horizon Sensor"); break;
    }

    fprintf(stdout, "%s", colour);
    fprintf(stdout, "[%s] ", identf);
    vfprintf(stdout, format, args);
    fprintf(stdout, "%s", KRES);
	fflush(stdout);
    va_end(args);
}


/**
 * Prints the current time in [h:m:s] format.
 */
static void printtime() {
    time_t timer;
    char buffer[25];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 25, "[%H:%M:%S]: ", tm_info);
    printf("%s",buffer);
}

#endif
