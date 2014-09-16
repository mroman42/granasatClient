#!/bin/bash
# This script can be used to execute granasatClient and obtain
# a clean log of the complete execution.

# Transforms the raw log into a clean log.
# Erases "color" characters.
raw_log() {
    sed 's/\\[32m//g 
         s/\\[0m//g
         s/\\[33//g
         s/\\[34m//g
         s/\\[35m//g
         s/\\[36m//g
         s/\\[37m//g
         s/\\[31m//g
         s/\\[1\;31m//g' < rawlog.log > granasatLog.log
}

# Trap code that will be executed if the main program is interrupted.
int_trap() {
    echo "[SCRIPT]: GranaSAT Client interrupted."
    raw_log
}

## MAIN SCRIPT
# Sets the trap.
trap int_trap INT

# Runs the program and image viewer
xdg-open ./images/image.bmp &
(./bin/granasatClient | tee rawlog.log) || true


# Cleans the log
raw_log

# Magnetometer and accelerometer measures
