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
// Location
const int LABELS_X_POS = 10;
const int LABELS_Y_POS_CPU = 10;
const int LABELS_Y_POS_INNER = 30;
const int LABELS_Y_POS_UPPER = 50;



/**
 * Refreshes a label with given new value.
 */
gboolean refreshLabel (GtkLabel* label, char* text, int new_value);

/**
 * Rewrites CPU Temperature.
 */
gboolean refreshCPUTemperature(GtkLabel* temp_label);

/**
 * Rewrites Inner Box Temperature.
 */
gboolean refreshInnerBoxTemperature (GtkLabel* temperature_label);

/**
 * Rewrites Upper Box Temperature.
 */
gboolean refreshUpperBoxTemperature (GtkLabel* temperature_label);

/**
 * Draws a graph using Cairo.
 */
void drawGraph();


int main (int argc, char* argv[])
{
	// GTK Builder
	GtkBuilder * builder;

	GtkWidget* main_window;
	GtkWidget* main_container;
	GtkWidget* cpu_temperature_label;
	GtkWidget* innerbox_temperature_label;
	GtkWidget* upperbox_temperature_label;

	GtkWidget* image_window;
	GtkWidget* image_container;
	GtkWidget* image;
	srand(time(NULL));


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


gboolean refreshLabel (GtkLabel* label, char* text, int new_value) {
	// Uses a buffer to print the new value in the text.
	char buffer[100];
	sprintf(buffer, text, new_value);
	gtk_label_set_text (label, buffer);

	// Returning True makes the loop continue
	return 1;
}


void drawGraph () {

}
