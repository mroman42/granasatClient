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


gboolean refreshCPUTemperature(GtkLabel* temp_label);


int main (int argc, char* argv[])
{
	GtkWidget* main_window;
	GtkWidget* main_container;
	GtkWidget* cpu_temperature_label;
	const int REFRESH_INTERVAL = 10;

	// Initialize GTK
	gtk_init (&argc, &argv);



	// Display the main window
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (main_window), "Client");
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 10);
	gtk_widget_show(main_window);

	// Create a fixed container
	main_container = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(main_window), main_container);
	gtk_widget_show(main_container);




	// CPU Temperature label
	cpu_temperature_label = gtk_label_new (NULL);
	g_timeout_add (REFRESH_INTERVAL, (GSourceFunc) refreshCPUTemperature, (gpointer) cpu_temperature_label);
	gtk_fixed_put (GTK_FIXED (main_container), cpu_temperature_label, 10, 10);
	gtk_widget_show (cpu_temperature_label);


	// Terminate application when window is destroyed
	g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	// GTK event loop
	gtk_main();

	return 0;
}


gboolean refreshCPUTemperature (GtkLabel* temperature_label) {
	// Reads Raspberry CPU Temperature
	// TO-DO
	srand(time(NULL));
	int new_temperature = rand();

	// Refreshes temperature label
	char buffer[100];
	sprintf(buffer,"CPU Temperature: %d ºC",(new_temperature+1)/10000000);
	gtk_label_set_text(temperature_label, buffer);

	return 1;
}
