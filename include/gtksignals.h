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

static void connect_all_signals (){
    // Draw signals
    g_signal_connect (G_OBJECT (drawing_area1), "draw", G_CALLBACK (drawGraph), MAG);
    g_signal_connect (G_OBJECT (drawing_area2), "draw", G_CALLBACK (drawGraph), ACC);
}

#endif
