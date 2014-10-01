/**
 * @file gtkrefresh.h
 * @author Mario Román
 * @date 24 Jun 2014
 * @brief Timeout functions management.
 * GTK timeout functions are defined in this file.
 */

// Avoids redefinition
#ifndef GTKREFRESH_H
#define GTKREFRESH_H

#include <gtk/gtk.h>
#include "gtkwidgets.h"
#include "data.h"
#include "client.h"

// Refresh intervals
const int REFRESH_INTERVAL_CONNECTION = 1000;
const int REFRESH_INTERVAL_IMAGE = 1;
const int REFRESH_INTERVAL_DATA = 5;
const int REFRESH_INTERVAL_REDRAW = 100;
const int REFRESH_INTERVAL_SYNCTIME = 300000; 

static void add_timeouts();
static gboolean checkServer();
static gboolean refreshMagnetometer();
static gboolean refreshAccelerometer();
static gboolean sendRedrawSignals();
static gboolean refreshConnectionLabel();
static gboolean readData();
static gboolean readImage();
static gboolean readCommands();
static gboolean refreshTempGeneral();
static gboolean refreshTempCamera();
static gboolean refreshTempCpu();
static gboolean refreshTempMagnetometer();
static gboolean syncTime();


/**
 * Adds all the timeout handlers to the GTK main loop.
 * This function has to be called in order to use the timeout functions into
 * the main loop. The timeout functions refresh the labels, graphs and status
 * of the program.
 */
static void add_timeouts() {
    // Client timeouts
    g_timeout_add (REFRESH_INTERVAL_CONNECTION, (GSourceFunc) checkServer, NULL);    
    g_timeout_add (REFRESH_INTERVAL_DATA, (GSourceFunc) readData, NULL);
    g_timeout_add (REFRESH_INTERVAL_IMAGE, (GSourceFunc) readImage, NULL);
    g_timeout_add (REFRESH_INTERVAL_DATA), (GSourceFunc) readCommands, NULL);

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

    // Sync time timeout
    g_timeout_add (REFRESH_INTERVAL_SYNCTIME, (GSourceFunc) syncTime, NULL);
}


// Timeout handlers
static gboolean readData() {
    if (CONNECTED)
        read_data_packet();
    return 1;
}

static gboolean readImage() {
    if (CONNECTED)
        read_image();
    return 1;
}

static gboolean readCommands() {
    if (CONNECTED)
        read_commands();
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

static gboolean syncTime() {
    sync_time();
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
