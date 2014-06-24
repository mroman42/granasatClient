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

#define FILEGLADE "glade/design.glade"

static void gtk_initialize (int argc, char* argv[]);
static void gtk_builder_initialize ();

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
    //add_main_notebook();
    
    // GTK main loop
    gtk_main();
}

/**
 * Initializes GTK builder.
 */
static void gtk_builder_initialize () {
     builder = gtk_builder_new();
     
     GError* err = NULL;
     if (gtk_builder_add_from_file(builder, FILEGLADE, &err) == 0)
         printf("%s",err->message);
}


#endif
