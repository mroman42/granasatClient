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
#include "gtkgui.h"

// Constants
const int ETHERNET_MAX = 1000;


int main (int argc, char* argv[])
{
	// GTK Builder
	GtkBuilder * builder;
	GtkWidget* main_window;
	GtkWidget* main_container;
	GtkWidget* ethernet_scale;
	GtkWidget* ethernet_limit_label;

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

	// Main Window and main container
	main_window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	main_container = GTK_WIDGET (gtk_builder_get_object (builder, "main_fixed"));
	gtk_widget_show (main_window);
	gtk_widget_show (main_container);

	// Temperature labels
	add_temperature_labels (builder);

	// Sliders
	ethernet_scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL,0,ETHERNET_MAX,1);
	ethernet_limit_label = GTK_WIDGET (gtk_builder_get_object (builder, "ethernet_limit_label"));
	gtk_range_set_value ((GtkRange*) ethernet_scale, 5);
	gtk_widget_set_size_request (ethernet_scale, 100,100);
	gtk_fixed_put (GTK_FIXED (main_container), ethernet_scale, 350, 340);
	gtk_widget_show (ethernet_scale);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshEthernetLimit, (gpointer) ethernet_limit_label);

	// Plots using Cairo.
	add_plots (builder, magnetometer_measures, accelerometer_measures);

	// Image displayer window
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

	return 0;
}
