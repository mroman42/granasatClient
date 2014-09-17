/**
 * @file gtksignals.h
 * @author Mario Román
 * @date 18 Jul 2014
 * @brief Widget signals management.
 * GTK signal handlers are defined in this file.
 */

// Avoids redefinition
#ifndef GTKSIGNALS_H
#define GTKSIGNALS_H

#include <gtk/gtk.h>
#include <glib.h>
#include "gtkgui.h"
#include "gtkgraph.h"
#include "data.h"

static void catalog_toggled             (GtkToggleButton *button, gpointer data);
static void altitude_toggled            (GtkToggleButton *button, gpointer data);
static void spin_vectors_changed        (GtkSpinButton *button, gpointer data);
static void spin_threshold_changed      (GtkSpinButton *button, gpointer data);
static void spin_roi_changed            (GtkSpinButton *button, gpointer data);
static void spin_points_changed         (GtkSpinButton *button, gpointer data);
static void spin_error_changed          (GtkSpinButton *button, gpointer data);
static void spin_brightness_changed     (GtkSpinButton *button, gpointer data);
static void spin_gamma_changed          (GtkSpinButton *button, gpointer data);
static void spin_gain_changed           (GtkSpinButton *button, gpointer data);
static void spin_exposure_value_changed (GtkSpinButton *button, gpointer data);
static void button_shutdown_clicked     (GtkButton *button, gpointer data);
static void button_restart_clicked      (GtkButton *button, gpointer data);
static void button_measures_clicked     (GtkButton *button, gpointer data);
static void scale_binthres_value_changed(GtkRange *range, gpointer data);
static void scale_canny_value_changed   (GtkRange *range, gpointer data);
static void scale_speed_changed         (GtkRange *range, gpointer data);
static void exposure_toggled (GtkToggleButton *button, gpointer data);

/**
 * Connects all the signals defined in the code to its respective GTK widgets.
 * It is necessary to call this function in order to use the GTK widgets interactively.
 */ 
static void connect_all_signals (){
    // Main signals
    g_signal_connect (G_OBJECT (button_shutdown), "clicked", G_CALLBACK (button_shutdown_clicked), NULL);
    g_signal_connect (G_OBJECT (button_restart),  "clicked", G_CALLBACK (button_restart_clicked),  NULL);
    g_signal_connect (G_OBJECT (button_start_measures), "clicked", G_CALLBACK (button_measures_clicked),  NULL);
    g_signal_connect (G_OBJECT (radiobutton_altitude1), "clicked", G_CALLBACK (altitude_toggled), GINT_TO_POINTER(1));
    g_signal_connect (G_OBJECT (radiobutton_altitude2), "clicked", G_CALLBACK (altitude_toggled), GINT_TO_POINTER(2));
    g_signal_connect (G_OBJECT (radiobutton_altitude3), "clicked", G_CALLBACK (altitude_toggled), GINT_TO_POINTER(3));
    g_signal_connect (G_OBJECT (scale_speed), "value_changed", G_CALLBACK (scale_speed_changed), NULL);

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

    // Camera signals
    g_signal_connect (G_OBJECT (spin_brightness),      "value_changed", G_CALLBACK (spin_brightness_changed),    NULL);
    g_signal_connect (G_OBJECT (spin_gamma),           "value_changed", G_CALLBACK (spin_gamma_changed),         NULL);
    g_signal_connect (G_OBJECT (spin_gain),            "value_changed", G_CALLBACK (spin_gain_changed),          NULL);
    g_signal_connect (G_OBJECT (spin_exposure_value),  "value_changed", G_CALLBACK (spin_exposure_value_changed),NULL);
    g_signal_connect (G_OBJECT (radiobutton_exp1), "clicked", G_CALLBACK (exposure_toggled), GINT_TO_POINTER(1));
    g_signal_connect (G_OBJECT (radiobutton_exp3), "clicked", G_CALLBACK (exposure_toggled), GINT_TO_POINTER(3));

    // Horizon Sensor signals
    g_signal_connect (G_OBJECT (scale_binthres), "value_changed", G_CALLBACK (scale_binthres_value_changed), NULL);
    g_signal_connect (G_OBJECT (scale_canny),    "value_changed", G_CALLBACK (scale_canny_value_changed),    NULL);
}


// Auxiliar event handler functions

static void catalog_toggled (GtkToggleButton *button, gpointer data) {
    if (gtk_toggle_button_get_active(button))
        set_magnitude(GPOINTER_TO_INT(data));
}

static void altitude_toggled (GtkToggleButton *button, gpointer data) {
    if (gtk_toggle_button_get_active(button))
        set_mode(GPOINTER_TO_INT(data));
}

static void exposure_toggled (GtkToggleButton *button, gpointer data) {
    if (gtk_toggle_button_get_active(button))
        set_exposure_mode(GPOINTER_TO_INT(data));
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
    set_error(gtk_spin_button_get_value(button));
}

static void spin_brightness_changed (GtkSpinButton *button, gpointer data) {
    set_brightness(gtk_spin_button_get_value_as_int(button));
}

static void spin_gamma_changed (GtkSpinButton *button, gpointer data) {
    set_gamma(gtk_spin_button_get_value_as_int(button));
}

static void spin_gain_changed (GtkSpinButton *button, gpointer data) {
    set_gain(gtk_spin_button_get_value_as_int(button));
}

static void spin_exposure_value_changed (GtkSpinButton *button, gpointer data) {
    set_exposure_value(gtk_spin_button_get_value_as_int(button));
}

static void button_shutdown_clicked (GtkButton *button, gpointer data) {
    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("My dialog", (GtkWindow*) main_window, flags, "OK", GTK_RESPONSE_ACCEPT, "Cancel", GTK_RESPONSE_REJECT, NULL);
    gint result = gtk_dialog_run (GTK_DIALOG (dialog));
    switch (result) {
        case GTK_RESPONSE_ACCEPT:
            send_shutdown();
            break;
    }
    gtk_widget_destroy (dialog);
}

static void button_restart_clicked  (GtkButton *button, gpointer data) {
    send_restart();
}

static void button_measures_clicked (GtkButton *button, gpointer data) {
    send_start_measures();
    send_all();
}

static void scale_binthres_value_changed (GtkRange *range, gpointer data) {
    set_binthres(gtk_range_get_value(range));
}

static void scale_canny_value_changed (GtkRange *range, gpointer data) {
    set_canny(gtk_range_get_value(range));
}

static void scale_speed_changed (GtkRange *range, gpointer data) {
    set_speed(gtk_range_get_value(range));
}


#endif
