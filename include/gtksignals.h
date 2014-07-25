/**
 * gtksignals.h
 * granaSAT.Client
 *
 *  Created on: Jul 18, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef GTKSIGNALS_H
#define GTKSIGNALS_H

#include <gtk/gtk.h>
#include <glib.h>
#include "gtkgui.h"
#include "gtkgraph.h"
#include "data.h"

static void catalog_toggled (GtkToggleButton *button, gpointer data);
static void spin_vectors_changed (GtkSpinButton *button, gpointer data);
static void spin_threshold_changed (GtkSpinButton *button, gpointer data);

static void connect_all_signals (){
    // Draw signals
    g_signal_connect (G_OBJECT (drawing_area1), "draw", G_CALLBACK (drawGraph), MAG);
    g_signal_connect (G_OBJECT (drawing_area2), "draw", G_CALLBACK (drawGraph), ACC);

    // Star Tracker signals
    g_signal_connect (G_OBJECT (radiobutton_catalog_1), "clicked", G_CALLBACK (catalog_toggled), GINT_TO_POINTER(1));
    g_signal_connect (G_OBJECT (radiobutton_catalog_2), "clicked", G_CALLBACK (catalog_toggled), GINT_TO_POINTER(2));
    g_signal_connect (G_OBJECT (radiobutton_catalog_3), "clicked", G_CALLBACK (catalog_toggled), GINT_TO_POINTER(3));
    g_signal_connect (G_OBJECT (radiobutton_catalog_4), "clicked", G_CALLBACK (catalog_toggled), GINT_TO_POINTER(4));
    g_signal_connect (G_OBJECT (radiobutton_catalog_5), "clicked", G_CALLBACK (catalog_toggled), GINT_TO_POINTER(5));
    g_signal_connect (G_OBJECT (radiobutton_catalog_6), "clicked", G_CALLBACK (catalog_toggled), GINT_TO_POINTER(6));
    g_signal_connect (G_OBJECT (spin_unitary_vectors), "value_changed", G_CALLBACK (spin_vectors_changed),   NULL);
    g_signal_connect (G_OBJECT (spin_threshold),       "value_changed", G_CALLBACK (spin_threshold_changed), NULL);
    g_signal_connect (G_OBJECT (spin_roi),             "value_changed", G_CALLBACK (spin_roi_changed),       NULL);
    g_signal_connect (G_OBJECT (spin_points),          "value_changed", G_CALLBACK (spin_points_changed),    NULL);
    g_signal_connect (G_OBJECT (spin_error),           "value_changed", G_CALLBACK (spin_error_changed),     NULL);
}

static void catalog_toggled (GtkToggleButton *button, gpointer data) {
    if (gtk_toggle_button_get_active(button))
        set_magnitude(GPOINTER_TO_INT(data));
}

static void spin_vectors_changed (GtkSpinButton *button, gpointer data) {
    set_unitary_vectors(gtk_spin_button_get_value_as_int(button));
}

static void spin_threshold_changed (GtkSpinButton *button, gpointer data) {
    set_threshold(gtk_spin_button_get_value_as_int(button));
}

static void spin_roi_changed (GtkSpinButton *button, gpointer data) {
    set_roi(gtk_spin_button_get_value_as_int(button));
}

static void spin_points_changed (GtkSpinButton *button, gpointer data) {
    set_points(gtk_spin_button_get_value_as_int(button));
}

static void spin_error_changed (GtkSpinButton *button, gpointer data) {
    set_error(gtk_spin_button_get_value_as_float(button));
}

#endif
