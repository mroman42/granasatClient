/*
 * main.c
 * granaSAT.Client 
 *
 *  Created on: Feb 22, 2014
 *      Author: Mario Román
 */

// GTK GUI library
#include <gtk/gtk.h>
#include <glib.h>
// Random numbers
#include <time.h>
#include <stdlib.h>


void refreshCPUTemperature(GtkLabel* temp_label);


int main (int argc, char* argv[])
{
	GtkWidget* main_window;
	GtkWidget* CPU_temperature_label;
	const int REFRESH_INTERVAL = 100;

	// Initialize GTK
	gtk_init (&argc, &argv);

	// Display the main window
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (main_window), "Client");
	gtk_widget_show(main_window);


	// CPU Temperature label
	CPU_temperature_label = gtk_label_new (NULL);
	//gtk_timeout_add (REFRESH_INTERVAL, refreshCPUTemperature, CPU_temperature_label);

	// Terminate application when window is destroyed
	g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// GTK event loop
	gtk_main();

	return 0;
}


void refreshCPUTemperature (GtkLabel* temperature_label) {
	// Reads Raspberry CPU Temperature
	// TO-DO
	srand(time(NULL));
	int new_temperature = rand();

	// Refreshes temperature label
	char buffer[100];
	sprintf(buffer,"%d",new_temperature+1);
	gtk_label_set_text(temperature_label, buffer);
}
