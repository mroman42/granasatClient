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
static GtkWidget*  drawing_area1;
static GtkWidget*  drawing_area2;
static GtkLabel*   status_connected_label;

static GtkWidget*  radiobutton_catalog_1;
static GtkWidget*  radiobutton_catalog_2;
static GtkWidget*  radiobutton_catalog_3;
static GtkWidget*  radiobutton_catalog_4;
static GtkWidget*  radiobutton_catalog_5;
static GtkWidget*  radiobutton_catalog_6;
static GtkWidget*  spin_unitary_vectors;

// Messages
char* MSG_CPU_TEMP           = "CPU Temperature:\t\t %4.3f ºC";
char* MSG_INNERBOX_TEMP      = "Inner Box Temperature:\t %4.3f ºC";
char* MSG_UPPERBOX_TEMP      = "Upper Box Temperature:\t %4.3f ºC";
char* MSG_ETHERNET_LIM       = "Ethernet speed:\t %5d Kbps";
char* MSG_MAGNETOMETER_DATA  = "Magnetometer data (Gauss):\n\tX: %4.3f\n\tY: %4.3f\n\tZ: %4.3f";
char* MSG_ACCELEROMETER_DATA = "Accelerometer data (G):\n\tX: %4.3f\n\tY: %4.3f\n\tZ: %4.3f";
char* MSG_CONNECTION_ON      = "Raspberry: Connected";
char* MSG_CONNECTION_OFF     = "Raspberry: Not Connected";

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
static GtkWidget* add_main_window() {
    GtkWidget* main_window = add_widget("main_window");
    g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    return main_window;
}


static GtkWidget* add_main_notebook() {
    return add_widget("main_notebook");
}

static GtkWidget* add_measures_container() {
    return add_widget("measures_fixed");
}

static GtkWidget* add_startracker_container() {
    return add_widget("startracker_fixed");
}

static GtkWidget* add_status_container() {
    return add_widget("status_fixed");
}

static GtkLabel* add_magnetometer_label() {
    return magnetometer_label = GTK_LABEL(add_widget("label_magnetometer"));
}

static GtkLabel* add_accelerometer_label() {
    return accelerometer_label = GTK_LABEL(add_widget("label_accelerometer"));
}

static GtkWidget* add_drawing_area1() {
    return drawing_area1 = add_widget("drawingarea1");
}

static GtkWidget* add_drawing_area2() {
    return drawing_area2 = add_widget("drawingarea2");
}

static GtkLabel* add_status_connected_label() {
    return status_connected_label = GTK_LABEL(add_widget("label_status_connected"));
}

static GtkWidget* add_catalog_size_group() {
    radiobutton_catalog_1 = add_widget("radiobutton_catalog1");
    radiobutton_catalog_2 = add_widget("radiobutton_catalog2");
    radiobutton_catalog_3 = add_widget("radiobutton_catalog3");
    radiobutton_catalog_4 = add_widget("radiobutton_catalog4");
    radiobutton_catalog_5 = add_widget("radiobutton_catalog5");
    radiobutton_catalog_6 = add_widget("radiobutton_catalog6");
    return radiobutton_catalog_1;
}

static GtkWidget* add_spin_vectors() {
    return spin_unitary_vectors = add_widget("spin_vectors");
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
    add_drawing_area1();
    add_drawing_area2();
    add_status_connected_label();
    add_catalog_size_group();
    add_spin_vectors();
}

#endif
