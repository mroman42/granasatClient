/**
 * gtkgui.c
 * granaSAT.Client
 *
 *  Created on: May 17, 2014
 *      Author: Mario Román
 */

#include <gtkgui.h>


void gtk_initialize (int argc, char* argv[]) {
    // Initialization
    gtk_init(&argc, &argv);

    // Adding widgets
    add_main_window();

    // GTK main loop
    gtk_main();
}
