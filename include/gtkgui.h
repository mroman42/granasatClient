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

GtkBuilder* builder = NULL;

static void gtk_initialize (int argc, char* argv[]);
static void gtk_builder_initialize () ;

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
static void gtk_builder_initialize () {
     builder = gtk_builder_new();
     gtk_builder_add_from_file(builder, FILEGLADE, NULL);
 }
#endif
