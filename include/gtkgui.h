/**
 * @file gtkgui.h
 * @author Mario Román
 * @date 17 May 2014
 * @brief Basic GTK management.
 */


// Avoids redefinition
#ifndef GTKGUI_H
#define GTKGUI_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "gtkwidgets.h"
#include "gtkrefresh.h"
#include "gtksignals.h"


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

    // Adds widgets
    add_all_widgets();
    
    // Adds timeouts
    add_timeouts();

    // Connects signals
    connect_all_signals();

    // GTK main loop
    gtk_main();
}

/**
 * Initializes GTK builder.
 */
static void gtk_builder_initialize () {
     builder = gtk_builder_new();
     
     GError* err = NULL;
     if (gtk_builder_add_from_file(builder, FILEGLADE, &err) == 0) {
         printf("ERROR in gtk_builder_initialize: %s\n",err->message);
	     exit(-1);
     }
}


#endif
