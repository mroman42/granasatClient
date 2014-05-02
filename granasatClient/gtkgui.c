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
char* MSG_MAGNETOMETER_DATA = "Magnetometer data (Gauss):\n\tX: %5f\n\tY: %5f\n\tZ: %5f";
char* MSG_ACCELEROMETER_DATA = "Accelerometer data (G):\n\tX: %5f\n\tY: %5f\n\tZ: %5f";


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
	//int upperbox_temperature = DATA.temp.highByte;

	float upperbox_temperature;

	if(DATA.temp.lowByte == 128 ) {
		upperbox_temperature = DATA.temp.highByte+0.5;
	}
	else {
		upperbox_temperature = DATA.temp.highByte;
	}


	// Refreshes temperature label
	return refreshLabel (temperature_label, MSG_UPPERBOX_TEMP, upperbox_temperature);
}

gboolean refreshMagnetometer (GtkLabel* mag_label) {
	char buffer[100];
	sprintf(buffer, MSG_MAGNETOMETER_DATA, MAG[0],MAG[1],MAG[2]);
	gtk_label_set_text (mag_label, buffer);

	return 1;
}

gboolean refreshAccelerometer (GtkLabel* acc_label) {
	char buffer[100];
	sprintf(buffer, MSG_ACCELEROMETER_DATA, ACC[0],ACC[1],ACC[2]);
	gtk_label_set_text (acc_label, buffer);

	return 1;
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

void drawGraph (GtkWidget* widget, cairo_t* cr, gpointer user_data) {
	float* measures = (float*) user_data;

	// Cairo initializing
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	// Axis
	const float HEIGHT = 200;
	const float WIDTH  = 300;
	const float SIN_60 = 0.8660254037844386;

	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2, 0.0);
	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2 + 2*HEIGHT/3*SIN_60,HEIGHT);
	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2 - 2*HEIGHT/3*SIN_60,HEIGHT);
	cairo_stroke (cr);

	// Vector
	printf("Measures: %5f,%5f,%5f", measures[0],measures[1],measures[2]);

	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
	cairo_line_to (cr, WIDTH/2 + SIN_60*measures[0]*4 -  SIN_60*measures[1]*4 , 2*HEIGHT/3-measures[2]*4);
	cairo_stroke (cr);
}

//void drawMagnetometer() {
//	// Cairo initializing
//	cairo_t* cr;
//	cairo_set_source_rgb(cr, 1, 1, 1);
//	cairo_paint(cr);
//
//	// Axis
//	const float HEIGHT = 200;
//	const float WIDTH  = 300;
//	const float SIN_60 = 0.8660254037844386;
//
//	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
//	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
//	cairo_line_to (cr, WIDTH/2, 0.0);
//	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
//	cairo_line_to (cr, WIDTH/2 + 2*HEIGHT/3*SIN_60,HEIGHT);
//	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
//	cairo_line_to (cr, WIDTH/2 - 2*HEIGHT/3*SIN_60,HEIGHT);
//	cairo_stroke (cr);
//
//	// Vector
//	printf("Measures: %5f,%5f,%5f", MAG[0],MAG[1],MAG[2]);
//
//	cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
//	cairo_move_to (cr, WIDTH/2, 2*HEIGHT/3);
//	cairo_line_to (cr, WIDTH/2 + SIN_60*MAG[0]*4 -  SIN_60*MAG[1]*4 , 2*HEIGHT/3-MAG[2]*4);
//	cairo_stroke (cr);
//}


void gpio_4_button_toggled_cb (GtkToggleButton *button, gpointer data) {
	if (gtk_toggle_button_get_active(button)) {
		printf("GPIO4 Button pressed\n");
		sendData(CTRL_LED_ON);
		sendData(4);
	}
	else {
		printf("GPIO4 Button released\n");
		sendData(CTRL_LED_OFF);
		sendData(4);
	}
}
