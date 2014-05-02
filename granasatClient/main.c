/*
 * main.c
 * granaSAT.Client 
 *
 *  Created on: Feb 22, 2014
 *      Author: Mario Román
 */

// Client libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "packet.h"
#include "client.h"
#include "measures.h"

// GTK GUI library
#include "gtkgui.h"

// Constants
const int ETHERNET_MAX = 1000;
const int IMAGE_SIZE = 1280*960;

void error(char *msg) {
	perror(msg);
	exit(1);
}


// Client/Server on Raspberry
void print_data (struct packet* data) {
	printf("Temperature\tHighByte: %d\n\t\tLowByte: %d\n", data->temp.highByte, data->temp.lowByte);
}


int main (int argc, char* argv[])
{
    // Initialize GTK.
    GtkBuilder* builder;
	GtkWidget* main_window;
	GtkWidget* main_container;

	gtk_init (&argc, &argv);
	srand(time(NULL));

	// Initialize Builder.
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, FILEGLADE, NULL);

	// Main Window and main container.
	main_window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	main_container = GTK_WIDGET (gtk_builder_get_object (builder, "main_fixed"));
	gtk_widget_show (main_window);
	gtk_widget_show (main_container);

	// Add widgets.
	add_temperature_labels (builder);
	add_ethernet_slider (builder, main_container);
	add_plots (builder, magnetometer_measures, accelerometer_measures);
	add_image_window();
	add_buttons(builder);

	// Building.

	gtk_window_set_keep_above ( (GtkWindow *) main_window, TRUE);


	// Terminate application when window is destroyed.
	g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// Client
    connect_server();
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //sendData(CTRL_LED_ON); sendData(27);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) read_server, (gpointer) &DATA);

	// GTK event loop.
	gtk_main();


	// Close server
	g_object_unref (G_OBJECT (builder));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//sendData(CTRL_LED_OFF); sendData(27);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sendData(-1);
	close(SOCKFD);

	return 0;
}




