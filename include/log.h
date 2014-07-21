/**
 * log.h
 * granaSAT.Client
 *
 *  Created on: Jul 11, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <time.h>

static void printlog(const char* msg);
static void printtime();


static void printlog(const char* msg) {
    printtime();
    printf("%s",msg);
}

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
