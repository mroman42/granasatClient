/**
 * protocol.h
 * granaSAT.Client/granaSAT.Server
 *
 *  Created on: Jul 24, 2014
 *      Author: Alejandro García, Mario Román
 */

// Avoids redefinition
#ifndef PROTOCOL_H
#define PROTOCOL_H


// COMMANDS
#define MSG_PASS          0    // 0. No operation
#define MSG_END           1    // 1. Ends connection
#define MSG_RESTART       2    // 2. Restarts connection
#define MSG_PING          3    // 3. Tests connection

#define MSG_SET_STARS     20   // 20. Sets centroids (+ int)
#define MSG_SET_CATALOG   21   // 21. Sets catalog   (+ int)
#define MSG_SET_PX_THRESH 22   // 22. Sets threshold (+ int)



#endif
