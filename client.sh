#!/bin/bash
# This script can be used to execute granasatClient and obtain
# a clean log of the complete execution.

# Environment variables
CLIENT=./bin/granasatClient
LOG_FOLDR=./log

# Transforms the raw log into a clean log.
# Erases "color" characters.
clean_log() {
    sed 's/\\[32m//g 
         s/\\[0m//g
         s/\\[33//g
         s/\\[34m//g
         s/\\[35m//g
         s/\\[36m//g
         s/\\[37m//g
         s/\\[31m//g
         s/\\[1\;31m//g' < $LOG_FOLDR/rawlog.log > $LOG_FOLDR/granasatLog.log
}

# Trap code that will be executed if the main program is interrupted.
int_trap() {
    echo "[SCRIPT]: GranaSAT Client interrupted."
    clean_log
}

## MAIN SCRIPT
# Sets the trap.
trap int_trap INT

# Writes the time in the log folder
LOG_FOLDR=$LOG_FOLDR`date +%s`
mkdir $LOG_FOLDR
echo "Log folder: $LOG_FOLDR"

# Runs the program and image viewer
xdg-open ./images/image.bmp &
($CLIENT | tee $LOG_FOLDR/rawlog.log) || true


# Cleans the log
clean_log

# Magnetometer, accelerometer and temperature measures
grep "Magnetometer measures:" $LOG_FOLDR/granasatLog.log | cut -d':' -f1,3,5  > $LOG_FOLDR/magnetometer_measures.log
grep "Accelerometer measures:" $LOG_FOLDR/granasatLog.log | cut -d':' -f1,3,5 > $LOG_FOLDR/accelerometer_measures.log
grep "temperature" $LOG_FOLDR/granasatLog.log | cut -d':' -f1,3,4,5 > $LOG_FOLDR/temperatures.log
