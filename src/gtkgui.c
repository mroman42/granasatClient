/**
 * gtkgui.c
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Román
 */

#include <gtkgui.h>

static GtkBuilder* builder;

void gtk_initialize (int argc, char* argv[]) {
    // Initialization
    gtk_init(&argc, &argv);
    gtk_builder_initialize();

    // Adding widgets
    add_main_window();

    // GTK main loop
    gtk_main();
}


void gtk_builder_initialize () {
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, FILEGLADE, NULL);
}
