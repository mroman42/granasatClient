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

extern GtkBuilder* builder;

/**
 * Main Window
 */
static GtkWidget* add_main_window (){
    GtkWidget* main_window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    gtk_widget_show(main_window);
    
    return main_window;
}


#endif
