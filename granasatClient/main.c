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
