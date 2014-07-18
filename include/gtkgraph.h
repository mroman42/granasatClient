/**
 * gtkgraph.h
 * granaSAT.Client
 *
 *  Created on: Jun 24, 2014
 *      Author: Mario Román
 */

// Avoids redefinition
#ifndef GTKGRAPH_H
#define GTKGRAPH_H

#include <gtk/gtk.h>
#include <glib.h>
#include <cairo.h>
#include "gtkgui.h"


static void drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data);

static void drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data) {
    // Measures
	float* measures = (float*) user_data;

	// Cairo initializing
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	// Axis
	const float HEIGHT = 200;
	const float WIDTH  = 300;
	const float SIN_60 = 0.8660254037844386;

	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_move_to (cr, WIDTH/2,  2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2,  0.0);
	cairo_move_to (cr, WIDTH/2,  2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2 + 2*HEIGHT/3*SIN_60,HEIGHT);
	cairo_move_to (cr, WIDTH/2,  2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2 - 2*HEIGHT/3*SIN_60,HEIGHT);
	cairo_stroke (cr);

	// Vector
	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2 + SIN_60*measures[0]*4 -  SIN_60*measures[1]*4 , 2*HEIGHT/3-measures[2]*4);
	cairo_stroke (cr);
}



#endif
