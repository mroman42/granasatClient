/**
 * gtkwidgets.h
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef GTKWIDGETS_H
#define GTKWIDGETS_H

#include <gtk/gtk.h>
#include <glib.h>
#include "gtkgui.h"

// Widget references
static GtkBuilder* builder;
static GtkLabel*   magnetometer_label;
static GtkLabel*   accelerometer_label;

// Messages
char* MSG_CPU_TEMP           = "CPU Temperature:\t\t %4.3f ºC";
char* MSG_INNERBOX_TEMP      = "Inner Box Temperature:\t %4.3f ºC";
char* MSG_UPPERBOX_TEMP      = "Upper Box Temperature:\t %4.3f ºC";
char* MSG_ETHERNET_LIM       = "Ethernet speed:\t %5d Kbps";
char* MSG_MAGNETOMETER_DATA  = "Magnetometer data (Gauss):\n\tX: %4.3f\n\tY: %4.3f\n\tZ: %4.3f";
char* MSG_ACCELEROMETER_DATA = "Accelerometer data (G):\n\tX: %4.3f\n\tY: %4.3f\n\tZ: %4.3f";

/**
 * Adds a widget given its name.
 */
static GtkWidget* add_widget(char* name) {
    GtkWidget* widget = GTK_WIDGET(gtk_builder_get_object(builder,name));
    gtk_widget_show(widget);
    return widget;
}

/**
 * Widgets
 */
static GtkWidget* add_main_window (){
    GtkWidget* main_window = add_widget("main_window");
    g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    return main_window;
}


static GtkWidget* add_main_notebook (){
    return add_widget("main_notebook");
}

static GtkWidget* add_measures_container (){
    return add_widget("measures_fixed");
}

static GtkWidget* add_startracker_container (){
    return add_widget("startracker_fixed");
}

static GtkWidget* add_status_container (){
    return add_widget("status_fixed");
}

static GtkLabel* add_magnetometer_label (){
    return magnetometer_label = GTK_LABEL(add_widget("label_magnetometer"));
}

static GtkLabel* add_accelerometer_label (){
    return accelerometer_label = GTK_LABEL(add_widget("label_accelerometer"));
}

/**
 * Adding all widgets
 */
static void add_all_widgets() {
    add_main_window();
    add_main_notebook();
    add_measures_container();
    add_startracker_container();
    add_status_container();
    add_magnetometer_label();
    add_accelerometer_label ();
}

#endif
