#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdlib.h>
#include "utilities.h"
#include "states.h"

#define ELEVATOR_NUMBER_OF_ORDERS 3

typedef struct Elevator {
    int queue_matrix[ELEVATOR_NUMBER_OF_ORDERS][HARDWARE_NUMBER_OF_FLOORS];

    /* Memory variables */
    int current_floor;
    int previous_floor;
    int current_movement;
    int last_dir;
    int current_order_dir;
    state current_state;
    
    /* Control variables */
    int stop_light_set;
    int timer_set;

} Elevator;

/*
Initializes the queue matrix to zero matrix. Current_floor to the current floor [0,4), or -1 if in the shaft. Current_dir to 1.
Current_state to INIT.
*/
void elevator_init(Elevator *p_elev);

//on startup takes the elevator to idle in floor
void elevator_startup_routine(Elevator *p_elev);

void elevator_order_light_on(Elevator *p_elev);

void elevator_update_floor(Elevator *p_elev);


#endif