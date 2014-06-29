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
const int REFRESH_INTERVAL = 50;


static void add_timeouts();
static gboolean checkServer();
static gboolean refreshMagnetometer();
static gboolean refreshAccelerometer();


static void add_timeouts() {
    // Client timeouts
    g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) checkServer, NULL);    

    // Data timeouts
    g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshMagnetometer, NULL);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshAccelerometer, NULL);
}

static gboolean checkServer() {
    check_connection();
    return 1;
}

static gboolean refreshMagnetometer() {
	char buffer[100];
	sprintf(buffer, MSG_MAGNETOMETER_DATA, MAG[0],MAG[1],MAG[2]);
	gtk_label_set_text (magnetometer_label, buffer);
	return 1;
}

static gboolean refreshAccelerometer () {
    char buffer[100];
    sprintf(buffer, MSG_ACCELEROMETER_DATA, ACC[0],ACC[1],ACC[2]);
    gtk_label_set_text (accelerometer_label, buffer);

    return 1;
}

#endif
