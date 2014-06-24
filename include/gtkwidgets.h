/**
 * gtkwidgets.h
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef GTKWIDGETS_H
#define GTKWIDGETS_H

#include <gtk/gtk.h>
#include <glib.h>
#include "gtkgui.h"

static GtkBuilder* builder = NULL;

/**
 * Main Window
 */
static GtkWidget* add_main_window (){
    GtkWidget* main_window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    gtk_widget_show(main_window);
    
    // Terminate application when window is destroyed.
    g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    
    return main_window;
}

/**
 * Main Container
 */
// static GtkWidget* add_main_notebook (){
//     GtkWidget* main_notebook = GTK_WIDGET(gtk_builder_get_object(builder,"main_notebook"));
//     gtk_widget_show(main_notebook);
//     return main_notebook;
// }

#endif
