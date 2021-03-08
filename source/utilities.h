#ifndef UTILITIES_H
#define UTILITIES_H

//returns the current floor, or -1 if the elevator is in the shaft
int read_all_floor_sensors();


void clear_all_order_lights(); //Originally this was declared a static void

//returns opposite direction of current_dir. If current_dir = 1 (Stop), opposite dir is also 1.
int elevator_opposite_dir(int current_dir);

#endif
