#ifndef UTILITIES_H
#define UTILITIES_H

//#include "timer.h"

//returns 1 if the elevator is entering the given floor (edge-triggered), returns 0 otherwise
int check_positive_edge_trigger_floor(int floor);

/*
//restarts timer if the obstruction is active. Returns when timer have finished successfully
void control_timer(int milliseconds);
*/

int read_all_floor_sensors();

#endif
