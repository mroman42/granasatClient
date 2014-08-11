/**
 * main.c
 * granaSAT.Client
 *
 *  Created on: May 16, 2014
 *      Author: Mario Román
 */

#include <gtkgui.h>
#include "data.h"

int main (int argc, char* argv[]) {
    // Sets working folder name
    set_working_folder_name();

    // Initialize GTK.
    gtk_initialize(argc, argv);
    printf("GTK closed\n");
    return 0;
}
