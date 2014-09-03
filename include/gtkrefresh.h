/**
 * gtkrefresh.h
 * granaSAT.Client
 *
 *  Created on: Jun 24, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef GTKREFRESH_H
#define GTKREFRESH_H

#include <gtk/gtk.h>
#include "gtkwidgets.h"
#include "data.h"
#include "client.h"

// Constants
const int REFRESH_INTERVAL_CONNECTION = 1000;
const int REFRESH_INTERVAL_IMAGE = 10;
const int REFRESH_INTERVAL_DATA = 5;
const int REFRESH_INTERVAL_REDRAW = 100;

static void add_timeouts();
static gboolean checkServer();
static gboolean refreshMagnetometer();
static gboolean refreshAccelerometer();
static gboolean sendRedrawSignals();
static gboolean refreshConnectionLabel();
static gboolean readData();
static gboolean readImage();
//static gboolean readImageBmp();
static gboolean refreshImage();
static gboolean refreshTempGeneral();
static gboolean refreshTempCamera();
static gboolean refreshTempCpu();
static gboolean refreshTempMagnetometer();


static void add_timeouts() {
    // Client timeouts
    g_timeout_add (REFRESH_INTERVAL_CONNECTION, (GSourceFunc) checkServer, NULL);    
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) readData, NULL);
    g_timeout_add (REFRESH_INTERVAL_IMAGE, (GSourceFunc) readImage, NULL);
    g_timeout_add (REFRESH_INTERVAL_IMAGE, (GSourceFunc) refreshImage, NULL);

    // Temperature label timeouts
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshTempGeneral, NULL);
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshTempCamera, NULL);
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshTempCpu, NULL);
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshTempMagnetometer, NULL);

    // Data timeouts
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshMagnetometer, NULL);
	g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshAccelerometer, NULL);

    // Status timeouts
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) refreshConnectionLabel, NULL);

    // Redraw timeouts
    g_timeout_add (REFRESH_INTERVAL_REDRAW, (GSourceFunc) sendRedrawSignals, NULL);
}



static gboolean readData() {
    if (CONNECTED)
        read_data_packet();
    return 1;
}

static gboolean refreshImage() {
    gtk_image_set_from_file((GtkImage*) image, IMAGE_FILE);
    return 1;
}

static gboolean readImage() {
    if (CONNECTED)
        read_image();
    return 1;
}

static gboolean checkServer() {
    check_connection();
    return 1;
}

static gboolean refreshMagnetometer() {
	char buffer[200];
	sprintf(buffer, MSG_MAGNETOMETER_DATA, MAG[0],MAG[1],MAG[2]);
	gtk_label_set_text (magnetometer_label, buffer);
	return 1;
}

static gboolean refreshAccelerometer() {
    char buffer[200];
    sprintf(buffer, MSG_ACCELEROMETER_DATA, ACC[0],ACC[1],ACC[2]);
    gtk_label_set_text (accelerometer_label, buffer);
    return 1;
}

static gboolean refreshTempGeneral() {
    char buffer[100];
    sprintf(buffer, MSG_TEMP_GENERAL, TEMP_GENERAL/1000.0);
    gtk_label_set_text (label_general_temp, buffer);
    return 1;
}

static gboolean refreshTempCamera() {
    char buffer[100];
    sprintf(buffer, MSG_TEMP_CAMERA, TEMP_CAMERA/1000.0);
    gtk_label_set_text (label_camera_temp, buffer);
    return 1;
}

static gboolean refreshTempCpu() {
    char buffer[100];
    sprintf(buffer, MSG_TEMP_CPU, TEMP_CPU/1000.0);
    gtk_label_set_text (label_cpu_temp, buffer);
    return 1;
}

static gboolean refreshTempMagnetometer() {
    char buffer[100];
    sprintf(buffer, MSG_TEMP_MAGNETOMETER, TEMP_MAGNETOMETER/1000.0);
    gtk_label_set_text (label_magnetometer_temp, buffer);
    return 1;
}

static gboolean sendRedrawSignals() {
	gtk_widget_queue_draw(drawing_area1);
	gtk_widget_queue_draw(drawing_area2);
	return 1;
}

static gboolean refreshConnectionLabel() {
    if (CONNECTED)
        gtk_label_set_text (status_connected_label, MSG_CONNECTION_ON);
    else
        gtk_label_set_text (status_connected_label, MSG_CONNECTION_OFF);
    return 1;
}

#endif
