/*
 * gtkgui.h
 * granaSAT.Client
 *
 *  Created on: Mar 22, 2014
 *      Author: Mario Román
 */

#ifndef GTKGUI_H_
#define GTKGUI_H_

// GTK GUI library
#include <gtk/gtk.h>
#include <glib.h>
#include <cairo.h>

// Files
#define FILEGLADE "client_design.glade"

/**
 * Constants and messages
 */
// Windows
const int REFRESH_INTERVAL = 1000;
const int MAIN_WINDOW_BORDER_WIDTH = 20;
const int IMAGE_WINDOW_BORDER_WIDTH = 0;

// Messages
char* MSG_CPU_TEMP      = "CPU Temperature:\t\t %5d ºC";
char* MSG_INNERBOX_TEMP = "Inner Box Temperature:\t %5d ºC";
char* MSG_UPPERBOX_TEMP = "Upper Box Temperature:\t %5d ºC";
char* MSG_ETHERNET_LIM  = "Ethernet speed:\t %5d Kbps";

// Location



#endif /* GTKGUI_H_ */
