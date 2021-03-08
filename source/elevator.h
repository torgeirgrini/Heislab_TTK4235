#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "queue_handler.h"
#include "hardware.h"
#include "states.h"

typedef struct Elevator {

    //queue handler matrix
    int **queue_handler;

    /* Control variables */

    //last floor sensor
    int current_floor;
    //current direction
    int current_dir;
    //last direction
    int last_dir;
    //direction of last order
    int current_order_dir;

    
    state current_state;
    
    int stop_light_set;
    int timer_set;

     
} Elevator;

/*
Initializes the queue matrix to zero matrix. Current_floor to the current floor [0,4), or -1 if in the shaft. Current_dir to 1.
Current_state to INIT.
*/
void init_elevator(Elevator *elev);




#endif