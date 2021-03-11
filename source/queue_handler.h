#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include "elevator.h"


#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

//Sets all elements of queue_matrix to zero.
void queue_clear(Elevator *p_elev);

//Returns 1 if there is and order at queue_matrix[order_type][floor]. 0 otherwise
int queue_get_order(Elevator *p_elev, HardwareOrder order_type, int floor);

//Updates queue_matrix with new orders
void queue_set_orders(Elevator *p_elev);

//Deletes the order at location queue_matrix[order_type][floor]
void queue_delete_order(Elevator *p_elev, HardwareOrder order_type, int floor);

//Returns 1 if there are any untreated orders at the floor, 0 otherwise
int queue_active_orders_floor(Elevator *p_elev, int floor);

//Iterates through all elements of queue_matrix to see if any orders are active. Returns 0 if there are active orders in 
//the upwards direction, 1 to indicate stop, 2 to indicate active orders in downwards direction
int queue_active_orders_all_floors(Elevator *p_elev);

//Looks for any order, returns movement direction of elevator
HardwareMovement queue_get_movement_any_direction(Elevator *p_elev);

//Returns direction of the next order to be treated
HardwareMovement queue_get_movement_direction(Elevator *p_elev);

//Returns the order type of the order which is to be treated
HardwareOrder queue_get_direction_of_order(Elevator *p_elev);

//Iterates through all elements of queue_matrix to see if any elements in the direction direction_type is set to 1. Returns 1 if it is, 0 otherwise.
int queue_active_orders_in_direction(Elevator *p_elev, HardwareMovement direction_type);

//Checks if any orders at the current floor are to be treated next
int queue_check_orders_current_floor(Elevator* p_elev);

#endif