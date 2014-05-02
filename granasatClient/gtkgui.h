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
#include "packet.h"
#include "client.h"

// Files
#define FILEGLADE "client_design.glade"


/**
 * Constants and messages
 */
extern const int ETHERNET_MAX;
extern int magnetometer_measures [];
extern int accelerometer_measures [];
extern struct packet DATA;

// Windows
const int REFRESH_INTERVAL;
const int MAIN_WINDOW_BORDER_WIDTH;
const int IMAGE_WINDOW_BORDER_WIDTH;
const char IMAGE_FILE [30];

// Messages
char* MSG_CPU_TEMP;
char* MSG_INNERBOX_TEMP;
char* MSG_UPPERBOX_TEMP;
char* MSG_ETHERNET_LIM;
char* MSG_MAGNETOMETER_DATA;
char* MSG_ACCELEROMETER_DATA;


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
 * Rewrites magnetometer and accelerometer data.
 */
gboolean refreshMagnetometer (GtkLabel* mag_label);
gboolean refreshAccelerometer (GtkLabel* acc_label);

/**
 * Rewrites Ethernet Limit.
 * @param ethernet_label
 */
gboolean refreshEthernetLimit (GtkLabel* ethernet_label);

/**
 * Draws a graph using Cairo.
 */
gboolean drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data);



/**
 * Adds the magnetometer and accelerometer drawing areas.
 * @param builder GTK builder.
 */
 static inline void add_plots (GtkBuilder* builder, int* magnetometer_measures, int* accelerometer_measures) {
	GtkWidget* drawing_area1 = GTK_WIDGET (gtk_builder_get_object (builder, "drawingarea1"));
	gtk_widget_show (drawing_area1);
	g_signal_connect (G_OBJECT (drawing_area1), "draw", G_CALLBACK (drawGraph), magnetometer_measures);

	GtkWidget* drawing_area2 = GTK_WIDGET (gtk_builder_get_object (builder, "drawingarea2"));
	gtk_widget_show (drawing_area2);
	g_signal_connect (G_OBJECT (drawing_area2), "draw", G_CALLBACK (drawGraph), accelerometer_measures);

	//g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) drawGraph, (gpointer) &DATA);
}

/**
 * Write temperature labels.
 * @param builder GTK builder.
 */
static inline void add_temperature_labels (GtkBuilder* builder) {
	GtkWidget* cpu_temperature_label;
	GtkWidget* innerbox_temperature_label;
	GtkWidget* upperbox_temperature_label;

	cpu_temperature_label = GTK_WIDGET (gtk_builder_get_object (builder, "cpu_temperature_label"));
	innerbox_temperature_label = GTK_WIDGET (gtk_builder_get_object (builder, "inner_temperature_label"));
	upperbox_temperature_label = GTK_WIDGET (gtk_builder_get_object (builder, "upper_temperature_label"));
	gtk_widget_show (cpu_temperature_label);
	gtk_widget_show (innerbox_temperature_label);
	gtk_widget_show (upperbox_temperature_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshCPUTemperature, (gpointer) cpu_temperature_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshInnerBoxTemperature, (gpointer) innerbox_temperature_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshUpperBoxTemperature, (gpointer) upperbox_temperature_label);
}


/**
 * Write data labels.
 * @param builder GTK builder.
 */
static inline void add_data_labels (GtkBuilder* builder) {
	GtkWidget* magnetometer_data_label;
	GtkWidget* accelerometer_data_label;

	magnetometer_data_label = GTK_WIDGET (gtk_builder_get_object  (builder, "magnetometer_data_label"));
	accelerometer_data_label = GTK_WIDGET (gtk_builder_get_object (builder, "accelerometer_data_label"));
	gtk_widget_show (magnetometer_data_label);
	gtk_widget_show (accelerometer_data_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshMagnetometer, (gpointer) magnetometer_data_label);
}

/**
 * Adds ethernet slider.
 */
static inline void add_ethernet_slider (GtkBuilder* builder, GtkWidget* main_container) {
	GtkWidget* ethernet_scale;
	GtkWidget* ethernet_limit_label;

	ethernet_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0,ETHERNET_MAX,1);
	ethernet_limit_label = GTK_WIDGET (gtk_builder_get_object (builder, "ethernet_limit_label"));
	gtk_range_set_value ((GtkRange*) ethernet_scale, 5);
	gtk_widget_set_size_request (ethernet_scale, 100,100);
	gtk_fixed_put (GTK_FIXED (main_container), ethernet_scale, 350, 340);
	gtk_widget_show (ethernet_scale);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshEthernetLimit, (gpointer) ethernet_limit_label);
}

/**
 * Adds image window.
 */
static inline void add_image_window () {
	GtkWidget* image_window;
	GtkWidget* image_container;
	GtkWidget* image;

	// Create the image displayer window
	image_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (image_window), "Images");
	gtk_container_set_border_width (GTK_CONTAINER (image_window), IMAGE_WINDOW_BORDER_WIDTH);
	gtk_window_set_accept_focus (GTK_WINDOW(image_window), FALSE);
	gtk_widget_show(image_window);

	// Create a fixed container
	image_container = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(image_window), image_container);
	gtk_widget_show(image_container);

	// Show sample image
	image = gtk_image_new_from_file(IMAGE_FILE);
	gtk_fixed_put (GTK_FIXED (image_container), image, 0, 0);
	gtk_widget_show(image);
}

/**
 * Adds image window.
 */
static inline void add_terminal (GtkBuilder* builder) {
	GtkWidget* terminal;
	terminal = GTK_WIDGET (gtk_builder_get_object (builder, "terminal1"));
	gtk_widget_show (terminal);
}


void gpio_4_button_toggled_cb(GtkToggleButton *button, gpointer data);


/**
 * Adds buttons.
 */
static inline void add_buttons (GtkBuilder* builder) {
	GtkWidget* gpio_button;
	gpio_button = GTK_WIDGET (gtk_builder_get_object (builder, "gpio_4_button"));
	g_signal_connect (GTK_WIDGET(gpio_button), "toggled", G_CALLBACK(gpio_4_button_toggled_cb), NULL);
	gtk_widget_show (gpio_button);
}



#endif /* GTKGUI_H_ */
