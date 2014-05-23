/**
 * gtkgui.h
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef GTKGUI_H
#define GTKGUI_H

#include <gtk/gtk.h>
#include "gtkwidgets.h"

#define FILEGLADE "glade/design2.glade"

static GtkBuilder* builder = NULL;

/**
 * Initializes GTK-GUI.
 * @param argc Number of arguments.
 * @param argv Arguments.
 */
static void gtk_initialize (int argc, char* argv[]) {
    // Initialization
    gtk_init(&argc, &argv);
    gtk_builder_initialize();

    // Adding widgets
    add_main_window();

    // GTK main loop
    gtk_main();
}

/**
 * Initializes GTK builder.
 */
 void gtk_builder_initialize ();

#endif
