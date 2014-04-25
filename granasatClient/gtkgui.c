/*
 * gtkgui.c
 * granaSAT.Client
 *
 *  Created on: Mar 22, 2014
 *      Author: Mario Román
 */

#include "gtkgui.h"

/**
 * Constants and messages
 */
// Windows
const int REFRESH_INTERVAL = 1000;
const int MAIN_WINDOW_BORDER_WIDTH = 20;
const int IMAGE_WINDOW_BORDER_WIDTH = 0;
const char IMAGE_FILE [] = "./images/image_received.data";

// Messages
char* MSG_CPU_TEMP      = "CPU Temperature:\t\t %5d ºC";
char* MSG_INNERBOX_TEMP = "Inner Box Temperature:\t %5d ºC";
char* MSG_UPPERBOX_TEMP = "Upper Box Temperature:\t %5d ºC";
char* MSG_ETHERNET_LIM  = "Ethernet speed:\t %5d Kbps";


gboolean refreshCPUTemperature (GtkLabel* temperature_label) {
	// Reads Raspberry CPU Temperature
	int cpu_temperature = rand()/10000000;

	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_CPU_TEMP, cpu_temperature);
}

gboolean refreshInnerBoxTemperature (GtkLabel* temperature_label) {
	// Reads Inner Box Temperature
	int innerbox_temperature = DATA.temp.lowByte;

	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_INNERBOX_TEMP, innerbox_temperature);
}

gboolean refreshUpperBoxTemperature (GtkLabel* temperature_label) {
	// Reads Inner Box Temperature
	int upperbox_temperature = DATA.temp.highByte;

	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_UPPERBOX_TEMP, upperbox_temperature);
}

gboolean refreshEthernetLimit (GtkLabel* ethernet_label) {
	// Reads Ethernet Limit
	int ethernet_limit = 20;

	// Refreshes Ethernet label
	return refreshLabel (ethernet_label, MSG_ETHERNET_LIM, ethernet_limit);
}

gboolean refreshLabel (GtkLabel* label, char* text, int new_value) {
	// Uses a buffer to print the new value in the text.
	char buffer[100];
	sprintf(buffer, text, new_value);
	gtk_label_set_text (label, buffer);

	// Returning True makes the loop continue
	return 1;
}


gboolean drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data) {
	int* measures = (int*) user_data;
	int i;

	// Cairo initializing
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	// Axis
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_move_to (cr, 0.0, 175.0);
	cairo_line_to (cr, 300.0, 175.0);
	cairo_move_to (cr, 25.0, 0.0);
	cairo_line_to (cr, 25.0, 200.0);
	cairo_stroke (cr);

	// Link each data point
	for (i = 0; i < 30; i ++)
		cairo_line_to (cr, i*10.0, 175.0-measures[i]);

	// Draw the curve
	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo_stroke (cr);

	return 1;
}


void gpio_4_button_pressed_cb (GtkToggleButton *button, gpointer data) {
	printf("gpio_4_button_pressed_cb");
	sendData(CTRL_LED_ON);
	sendData(4);
}


void gpio_4_button_released_cb (GtkToggleButton *button, gpointer data) {
	sendData(CTRL_LED_OFF);
	sendData(4);
}
