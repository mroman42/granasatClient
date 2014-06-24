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

// Widget references
static GtkBuilder* builder = NULL;


/**
 * Adds a widget given its name.
 */
static GtkWidget* add_widget(char* name) {
    GtkWidget* widget = GTK_WIDGET(gtk_builder_get_object(builder,name));
    gtk_widget_show(widget);
    return widget;
}

/**
 * Widgets
 */
static GtkWidget* add_main_window (){
    GtkWidget* main_window = add_widget("main_window");
    g_signal_connect (main_window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    return main_window;
}


static GtkWidget* add_main_notebook (){
    return add_widget("main_notebook");
}

static GtkWidget* add_measures_container (){
    return add_widget("measures_fixed");
}

static GtkWidget* add_startracker_container (){
    return add_widget("startracker_fixed");
}

static GtkWidget* add_status_container (){
    return add_widget("status_fixed");
}

static GtkWidget* add_magnetometer_label (){
    return add_widget("label_magnetometer");
}

static GtkWidget* add_accelerometer_label (){
    return add_widget("label_accelerometer");
}

/**
 * Adding all widgets
 */
static void add_all_widgets(){
    add_main_window();
    add_main_notebook();
    add_measures_container();
    add_startracker_container();
    add_status_container();
    add_magnetometer_label();
    add_accelerometer_label ();
}

#endif
