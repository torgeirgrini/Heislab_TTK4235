/**
 * @file
 * @brief A library for an Elevator struct, and for operations on Elevator struct
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdlib.h>
#include "utilities.h"
#include "states.h"

#define ELEVATOR_NUMBER_OF_ORDERS 3

/**
 * @brief An Elevator struct which holds a queue system, memory variables and control variables
 * 
 * @param queue_matrix A matrix that a value of every type of order at every floor for the elevator. The values
 * are 0 for a none active order, and non-zero for an active order
 * @param current_floor Holds the value for the current or last visited floor
 * @param previous_floor Holds the value for the previous visited floor
 * @param current_movement Holds the value for the current direction of the elevator
 * @param last_dir Holds the value for the previous direction of the elevator
 * @param current_order_dir Holds the value for the order type of the last handled order
 * @param current_state Holds the current state for the elevator
 * @param stop_light_set A truthy value for if the stop light is set
 * @param timer_set A truthy value for if the timer has been set
 * 
*/
typedef struct Elevator {
    int queue_matrix[ELEVATOR_NUMBER_OF_ORDERS][HARDWARE_NUMBER_OF_FLOORS];

    /* Memory variables */
    int current_floor;
    int previous_floor;
    HardwareMovement current_movement;
    HardwareMovement last_dir;
    HardwareOrder current_order_dir;
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