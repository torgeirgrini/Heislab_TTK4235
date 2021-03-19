/**
 * @file
 * @brief Library for an Elevator struct, and for operations on an Elevator struct
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "utilities.h"
#include "states.h"

#define ELEVATOR_NUMBER_OF_ORDERS 3

/**
 * @brief An Elevator struct which holds a queue system, memory variables and control variables
 * 
 * @param queue_matrix A matrix that holds a value for every type of order at every floor for the elevator. The values
 * are non-zero for an active order and zero for a none-active order
 * @param current_floor Holds the value for the current or last visited floor
 * @param previous_floor Holds the value for the previously visited floor
 * @param current_movement Holds the value for the current direction of the elevator
 * @param previous_direction Holds the value for the previous direction of the elevator
 * @param order_direction Holds the value for the order type of the last handled order
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
    HardwareMovement previous_direction;
    HardwareOrder order_direction;
    state current_state;
    
    /* Control variables */
    int stop_light_set;
    int timer_set;

} Elevator;


/**
 * @brief Initialises the elements of @p p_elev and sets queue_matrix to a zero matrix. Sets current_state to INIT.
 * 
 * @param[out] p_elev Pointer to an Elevator struct
 */
void elevator_init(Elevator *p_elev);

/**
 * @brief Moves the elevator to a defined state and sets current_movement, 
 * current_direction and previous_direction in @p p_elev. Sets current_state to IDLE_IN_FLOOR upon success
 * 
 * @param[out] p_elev Pointer to an Elevator struct
 */ 
void elevator_startup_routine(Elevator *p_elev);

/**
 * @brief Sets the order lights for the order types and floors
 * 
 * @param[in] p_elev Pointer to an Elevator struct
 */
void elevator_set_order_light(Elevator *p_elev);

/**
 * @brief Updates current_floor and previous_floor in @p p_elev and sets the floor indicator
 * 
 * @param[in, out] p_elev
 */
void elevator_update_floor(Elevator *p_elev);

/**
 * @brief Detects if the stop button is pressed, and decides the behavior of the elevator if it is.
 * If a floor sensor is activated the state of the elevator is to be set to STOP_BTN_FLOOR.
 * Otherwise the state of the elevator is to be set to STOP_BTN_SHAFT.
 * @param[in,out] p_elev Pointer to an Elevator struct 
 */
void elevator_emergency_detector(Elevator *p_elev);


#endif