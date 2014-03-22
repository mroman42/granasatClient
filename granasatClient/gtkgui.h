/*
 * gtkgui.h
 * granaSAT.Client
 *
 *  Created on: Mar 22, 2014
 *      Author: Mario Román
 */

#ifndef GTKGUI_H_
#define GTKGUI_H_

// GTK GUI library
#include <gtk/gtk.h>
#include <glib.h>
#include <cairo.h>

// Random numbers
#include <time.h>
#include <stdlib.h>

// Files
#define FILEGLADE "client_design.glade"

/**
 * Constants and messages
 */
// Windows
const int REFRESH_INTERVAL;
const int MAIN_WINDOW_BORDER_WIDTH;
const int IMAGE_WINDOW_BORDER_WIDTH;

// Messages
char* MSG_CPU_TEMP;
char* MSG_INNERBOX_TEMP;
char* MSG_UPPERBOX_TEMP;
char* MSG_ETHERNET_LIM;

// Location




/**
 * Refreshes a label with given new value.
 */
gboolean refreshLabel (GtkLabel* label, char* text, int new_value);

/**
 * Rewrites CPU, inner box and upper box temperatures.
 */
gboolean refreshCPUTemperature (GtkLabel* temp_label);
gboolean refreshInnerBoxTemperature (GtkLabel* temperature_label);
gboolean refreshUpperBoxTemperature (GtkLabel* temperature_label);

/**
 * Rewrites Ethernet Limit
 */
gboolean refreshEthernetLimit (GtkLabel* ethernet_label);

/**
 * Draws a graph using Cairo.
 */
gboolean drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data);


#endif /* GTKGUI_H_ */
