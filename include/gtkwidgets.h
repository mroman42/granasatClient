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

// WIDGET REFERENCES
// General
static GtkBuilder* builder;
static GtkLabel*   magnetometer_label;
static GtkLabel*   accelerometer_label;
static GtkWidget*  drawing_area1;
static GtkWidget*  drawing_area2;
static GtkLabel*   status_connected_label;
static GtkWidget*  scale_speed;
static GtkWidget*  image;
// Main
static GtkWidget*  button_shutdown;
static GtkWidget*  button_restart;
static GtkWidget*  radiobutton_altitude1;
static GtkWidget*  radiobutton_altitude2;
static GtkWidget*  radiobutton_altitude3;
static GtkLabel*   label_general_temp;
static GtkLabel*   label_camera_temp;
static GtkLabel*   label_magnetometer_temp;
static GtkLabel*   label_cpu_temp;
// Star Tracker tab
static GtkWidget*  radiobutton_catalog_1;
static GtkWidget*  radiobutton_catalog_2;
static GtkWidget*  radiobutton_catalog_3;
static GtkWidget*  radiobutton_catalog_4;
static GtkWidget*  radiobutton_catalog_5;
static GtkWidget*  radiobutton_catalog_6;
static GtkWidget*  spin_unitary_vectors;
static GtkWidget*  spin_threshold;
static GtkWidget*  spin_roi;
static GtkWidget*  spin_points;
static GtkWidget*  spin_error;
// Camera tab
static GtkWidget*  spin_brightness;
static GtkWidget*  spin_gamma;
static GtkWidget*  spin_gain;
static GtkWidget*  spin_exposure_value;
// Horizon Sensor
static GtkWidget*  scale_binthres;
static GtkWidget*  scale_canny;


// Messages
char* MSG_CPU_TEMP           = "CPU Temperature:\t\t %4.3f ºC";
char* MSG_INNERBOX_TEMP      = "Inner Box Temperature:\t %4.3f ºC";
char* MSG_UPPERBOX_TEMP      = "Upper Box Temperature:\t %4.3f ºC";
char* MSG_ETHERNET_LIM       = "Ethernet speed:\t %5d Kbps";
char* MSG_MAGNETOMETER_DATA  = "Magnetometer data (Gauss):\n\tX: %4.3f\n\tY: %4.3f\n\tZ: %4.3f";
char* MSG_ACCELEROMETER_DATA = "Accelerometer data (G):\n\tX: %4.3f\n\tY: %4.3f\n\tZ: %4.3f";
char* MSG_CONNECTION_ON      = "Raspberry: Connected";
char* MSG_CONNECTION_OFF     = "Raspberry: Not Connected";
char* MSG_TEMP_GENERAL       = "General temperature: \t%d";
char* MSG_TEMP_CAMERA        = "Camera temperature: \t%d";
char* MSG_TEMP_CPU           = "CPU temperature: \t%d";
char* MSG_TEMP_MAGNETOMETER  = "Magnetometer temperature: \t%d";

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
    gtk_window_set_keep_above((GtkWindow *) main_window, TRUE);
    return main_window;
}

static GtkWidget* add_image_window() {
    GtkWidget* image_window = add_widget("image_window");
    gtk_window_set_title (GTK_WINDOW (image_window), "Images");
    return image_window;
}

static GtkWidget* add_image() {
    return image = add_widget("image");
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

static GtkWidget* add_altitude_size_group() {
    radiobutton_altitude1 = add_widget("radiobutton_altitude1");
    radiobutton_altitude2 = add_widget("radiobutton_altitude2");
    radiobutton_altitude3 = add_widget("radiobutton_altitude3");
    return radiobutton_altitude1;
}

static GtkWidget* add_spin_vectors() {
    return spin_unitary_vectors = add_widget("spin_vectors");
}

static GtkWidget* add_spin_threshold() {
    return spin_threshold = add_widget("spin_threshold");
}

static GtkWidget* add_spin_roi() {
    return spin_roi = add_widget("spin_roi");
}

static GtkWidget* add_spin_points() {
    return spin_points = add_widget("spin_points");
}

static GtkWidget* add_spin_error() {
    return spin_error = add_widget("spin_error");
}

static GtkWidget* add_spin_brightness() {
    return spin_brightness = add_widget("spin_brightness");
}

static GtkWidget* add_spin_gamma() {
    return spin_gamma = add_widget("spin_gamma");
}

static GtkWidget* add_spin_gain() {
    return spin_gain = add_widget("spin_gain");
}

static GtkWidget* add_spin_exposure_value() {
    return spin_exposure_value = add_widget("spin_exposure_value");
}

static GtkWidget* add_button_shotudown() {
    return button_shutdown = add_widget("button_shutdown");
}

static GtkWidget* add_button_restart() {
    return button_restart = add_widget("button_restart");
}

static GtkWidget* add_scale_speed() {
    return scale_speed = add_widget("scale_speed");
}

static GtkWidget* add_scale_binthres() {
    return scale_binthres = add_widget("scale_binthres");
}

static GtkWidget* add_scale_canny() {
    return scale_canny = add_widget("scale_canny");
}

static void add_label_temperatures() {
    label_general_temp = GTK_LABEL(add_widget("label_general_temp"));
    label_camera_temp = GTK_LABEL(add_widget("label_camera_temp"));
    label_magnetometer_temp = GTK_LABEL(add_widget("label_magnetometer_temp"));
    label_cpu_temp = GTK_LABEL(add_widget("label_cpu_temp"));
}

/*
   Adds all widgets
 */
static void add_all_widgets() {
    add_image_window();
    add_image();
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
    add_spin_threshold();
    add_spin_roi();
    add_spin_points();
    add_spin_error();
    add_spin_brightness();
    add_spin_gamma();
    add_spin_gain();
    add_spin_exposure_value();
    add_button_restart();
    add_button_shotudown();
    add_scale_speed();
    add_scale_binthres();
    add_scale_canny();
    add_altitude_size_group();
    add_label_temperatures();
}

#endif
