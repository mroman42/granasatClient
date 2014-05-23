/**
 * gtkwidgets.c
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Román
 */

#include "gtkwidgets.h"

GtkWidget* add_main_window () {
    GtkWidget* main_window = GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
    gtk_widget_show(main_window);
    
    return main_window;
}
