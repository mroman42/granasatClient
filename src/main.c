/**
 * @file main.c
 * @author Mario Román
 * @date 16 May 2014
 * @brief Attitude determination for a pico satellite based in a star tracker and 
Earth’s magnetic field measurements

 * @mainpage GranaSAT Client Documentation
 * @section what_sec GranaSAT: what and why?
 * Pico and nano satellite used for research and study have specific attitude 
determination methods and associated sensors. Apart from sun sensors and 
magnetometers, accurate attitude determination sensor systems are not yet available 
for small satellites. The star sensor is the best option in terms of accuracy and 
performance. However, the major drawbacks of developing these systems are cost, 
weight and the effort required in the production process. This is why GranaSAT team 
is going to design and build a <b> low-cost attitude determination system</b>. The team will 
test the system, which is going to be based in a <b>star sensor</b>, a <b>horizon sensor</b> and the 
<b>magnetic field measurements</b> provided by a magnetometer. 
The same Charge Coupled Device is going to be used for both the star sensor and the 
horizon sensor to obtain the orientation of the gondola. Furthermore, we will estimate 
the attitude off-board by using the magnetic field measurements obtained during the 
flight.

 * @section mission_sec Mission statement
 * The GranaSAT experiment aims to study the orientation determination in satellites. 
A device called <b> star tracker </b> is normally used to obtain the information about the 
orientation of a satellite in 3-dimensional coordinates. However, if the camera fails to 
detect the stellar field, we will use the measurements provided by the <b> magnetometer 
sensor</b>, the <b> accelerometer sensor </b> and a <b> horizon sensor </b> to calculate the attitude. 
The experiment is designed to be placed in a university GranaSAT pico satellite. 
Hence, performing the experiment in conditions environmentally similar to those in 
outer space may be very instructive for us. 

 * @section objectives_sec Experiment objectives
 * <b> Primary objectives </b>
 * - The main objective of this experiment is to build and test in real conditions an 
attitude measurement system during the BEXUS 19 campaign.
 * - To test the accuracy of the attitude measurement system using a star sensor.
 * - To test the accuracy of the attitude measurement system using a horizon 
sensor.
 * - To test the accuracy of the attitude measurement system using a 
magntometer.
 * - To check whether or not the attitude system is adequate for the GranaSAT pico 
satellite. 

 * <b> Secondary objectives </b>
 * - To gain know-how about space missions and their future application in other 
UGR space projects.
 * - To learn how to document a space related project.
 * - To improve cooperative work skills.
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
