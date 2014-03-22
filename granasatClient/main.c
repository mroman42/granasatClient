/*
 * main.c
 * granaSAT.Client 
 *
 *  Created on: Feb 22, 2014
 *      Author: Mario Román
 */

// Client libraries
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

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
const int REFRESH_INTERVAL = 1000;
const int MAIN_WINDOW_BORDER_WIDTH = 20;
const int IMAGE_WINDOW_BORDER_WIDTH = 0;
// Messages
char* MSG_CPU_TEMP = "CPU Temperature:\t\t %5d ºC";
char* MSG_INNERBOX_TEMP = "Inner Box Temperature:\t %5d ºC";
char* MSG_UPPERBOX_TEMP = "Upper Box Temperature:\t %5d ºC";
char* MSG_ETHERNET_LIM = "Ethernet speed:\t %5d Kbps";
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
static gboolean drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data);


int main (int argc, char* argv[])
{
	// GTK Builder
	GtkBuilder * builder;

	GtkWidget* main_window;
	GtkWidget* main_container;
	GtkWidget* cpu_temperature_label;
	GtkWidget* innerbox_temperature_label;
	GtkWidget* upperbox_temperature_label;
	GtkWidget* ethernet_scale;
	GtkWidget* ethernet_limit_label;

	GtkWidget* image_window;
	GtkWidget* image_container;
	GtkWidget* image;

	// Measures
	srand(time(NULL));
	int magnetometer_measures []  = {10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43,34,35,34,23,34};
	int accelerometer_measures [] = {10,20,10,35,98,10,20,40,35,13,50,20,16,35,90,17,20,12,35,98,43,20,10,35,78,10,5,10,35,43};



	// Initialize GTK
	gtk_init (&argc, &argv);


	/////
	// Initialize Builder
	/////
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, FILEGLADE, NULL);

	// Main Window
	main_window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	gtk_widget_show (main_window);


	// Main Container
	main_container = GTK_WIDGET (gtk_builder_get_object (builder, "main_fixed"));
	gtk_widget_show(main_container);


	// Temperature labels
	cpu_temperature_label = GTK_WIDGET (gtk_builder_get_object (builder, "cpu_temperature_label"));
	innerbox_temperature_label = GTK_WIDGET (gtk_builder_get_object (builder, "inner_temperature_label"));
	upperbox_temperature_label = GTK_WIDGET (gtk_builder_get_object (builder, "upper_temperature_label"));
	gtk_widget_show (cpu_temperature_label);
	gtk_widget_show (innerbox_temperature_label);
	gtk_widget_show (upperbox_temperature_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshCPUTemperature, (gpointer) cpu_temperature_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshInnerBoxTemperature, (gpointer) innerbox_temperature_label);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshUpperBoxTemperature, (gpointer) upperbox_temperature_label);


	// Sliders
	ethernet_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0,100,1);
	ethernet_limit_label = GTK_WIDGET (gtk_builder_get_object (builder, "ethernet_limit_label"));
	gtk_range_set_value (ethernet_scale, 5);
	gtk_widget_set_size_request (ethernet_scale, 100,100);
	gtk_fixed_put (GTK_FIXED (main_container), ethernet_scale, 350, 340);
	gtk_widget_show (ethernet_scale);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshEthernetLimit, (gpointer) ethernet_limit_label);


	/////
	// Draw plot using Cairo.
	/////
	GtkWidget* drawing_area1 = GTK_WIDGET (gtk_builder_get_object (builder, "drawingarea1"));
	gtk_widget_show (drawing_area1);
	g_signal_connect (G_OBJECT (drawing_area1), "draw", G_CALLBACK (drawGraph), magnetometer_measures);

	GtkWidget* drawing_area2 = GTK_WIDGET (gtk_builder_get_object (builder, "drawingarea2"));
	gtk_widget_show (drawing_area2);
	g_signal_connect (G_OBJECT (drawing_area2), "draw", G_CALLBACK (drawGraph), accelerometer_measures);

	/////
	// Building
	/////
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref (G_OBJECT (builder));
	gtk_window_set_keep_above ( (GtkWindow *) main_window, TRUE);


	////
	// Image Window
	////
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


	// Terminate application when window is destroyed
	g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// GTK event loop.
	gtk_main();

	return 0;
}




gboolean refreshCPUTemperature (GtkLabel* temperature_label) {
	// Reads Raspberry CPU Temperature
	// TO-DO
	int cpu_temperature = rand()/10000000;

	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_CPU_TEMP, cpu_temperature);
}


gboolean refreshInnerBoxTemperature (GtkLabel* temperature_label) {
	// Reads Inner Box Temperature
	// TO-DO
	int innerbox_temperature = rand()/10000000;

	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_INNERBOX_TEMP, innerbox_temperature);
}

gboolean refreshUpperBoxTemperature (GtkLabel* temperature_label) {
	// Reads Inner Box Temperature
	// TO-DO
	int upperbox_temperature = rand()/10000000;

	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_UPPERBOX_TEMP, upperbox_temperature);
}

gboolean refreshEthernetLimit (GtkLabel* ethernet_label) {
	// Reads Ethernet Limit
	int ethernet_limit = 20;

	// Refreshes Ethernet label
	return refreshLabel (ethernet_label, MSG_ETHERNET_LIM, ethernet_limit);
}

gboolean refreshLabel (GtkLabel* label, char* text, int new_value) {
	// Uses a buffer to print the new value in the text.
	char buffer[100];
	sprintf(buffer, text, new_value);
	gtk_label_set_text (label, buffer);

	// Returning True makes the loop continue
	return 1;
}


static gboolean drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data) {
	int* measures = (int*) user_data;
	int i;

	// Cairo initializing
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	// Axis
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_move_to (cr, 0.0, 175.0);
	cairo_line_to (cr, 300.0, 175.0);
	cairo_move_to (cr, 25.0, 0.0);
	cairo_line_to (cr, 25.0, 200.0);
	cairo_stroke (cr);

	// Link each data point
	for (i = 0; i < 30; i ++)
		cairo_line_to (cr, i*10.0, 175.0-measures[i]);

	// Draw the curve
	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo_stroke (cr);

	return 1;
}
