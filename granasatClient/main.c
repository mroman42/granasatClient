/*
 * main.c
 * granaSAT.Client 
 *
 *  Created on: Feb 22, 2014
 *      Author: Mario Román
 */

#include <gtk/gtk.h>
#include <glib.h>

int main (int argc, char* argv[])
{
	GtkWidget* main_window;

	// Initialize GTK
	gtk_init (&argc, &argv);

	//Display the main window
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(main_window);

	// GTK event loop
	gtk_main();

	return 0;
}
