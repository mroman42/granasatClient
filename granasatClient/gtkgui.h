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
extern const int ETHERNET_MAX;
extern int magnetometer_measures [];
extern int accelerometer_measures [];

// Windows
const int REFRESH_INTERVAL;
const int MAIN_WINDOW_BORDER_WIDTH;
const int IMAGE_WINDOW_BORDER_WIDTH;

// Messages
char* MSG_CPU_TEMP;
char* MSG_INNERBOX_TEMP;
char* MSG_UPPERBOX_TEMP;
char* MSG_ETHERNET_LIM;



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
	image = gtk_image_new_from_file("./sample_images/sample1.jpg");
	gtk_fixed_put (GTK_FIXED (image_container), image, 0, 0);
	gtk_widget_show(image);
}

/**
 * Creates GUI.
 */
static inline void initialize_gtk (int argc, char* argv[], int magnetometer_measures[], int accelerometer_measures[]) {
	GtkBuilder* builder;
	GtkWidget* main_window;
	GtkWidget* main_container;

	// Initialize GTK
	gtk_init (&argc, &argv);
	srand(time(NULL));

	/////
	// Initialize Builder
	/////
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, FILEGLADE, NULL);

	// Main Window and main container
	main_window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	main_container = GTK_WIDGET (gtk_builder_get_object (builder, "main_fixed"));
	gtk_widget_show (main_window);
	gtk_widget_show (main_container);

	// Add widgets.
	add_temperature_labels (builder);
	add_ethernet_slider (builder, main_container);
	add_plots (builder, magnetometer_measures, accelerometer_measures);
	add_image_window();

	/////
	// Building
	/////
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref (G_OBJECT (builder));
	gtk_window_set_keep_above ( (GtkWindow *) main_window, TRUE);


	// Terminate application when window is destroyed
	g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// GTK event loop.
	gtk_main();
}

#endif /* GTKGUI_H_ */
