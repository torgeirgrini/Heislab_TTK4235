#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "queue_handler.h"
#include "hardware.h"
#include "states.h"

typedef struct Elevator {
    //queue handler matrix
    int **queue_handler;

    //last floor sensor
    int current_floor;

    //current or last known direction
    int current_dir;

    //current state
    state current_state;
    
    int stop_light_set;
    
} Elevator;

/*
Initializes the queue matrix to zero matrix. Current_floor to the current floor [0,4), or -1 if in the shaft. Current_dir to 1.
Current_state to INIT.
*/
void init_elevator(Elevator *elev);

//returns opposite direction of current_dir. If current_dir = 1 (Stop), opposite dir is also 1.
int elevator_opposite_dir(int current_dir);



#endif