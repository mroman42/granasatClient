/**
 * gtkgui.c
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Rom�n
 */

#include <gtkgui.h>


void gtk_builder_initialize () {
    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, FILEGLADE, NULL);
}
