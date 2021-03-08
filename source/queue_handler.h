#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include "hardware.h"
#include "elevator.h"

#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

//Sets all elements of queue_matrix to zero.
void queue_clear(Elevator *elev);

//Updates queue_matrix with new orders
void queue_set_orders(Elevator *elev);

//Returns 1 if there is and order at queue_matrix[order_type][floor]. 0 otherwise
int queue_get_order(Elevator *elev, int order_type, int floor);

//Deletes the order at location queue_matrix[order_type][floor]
void queue_delete_order(Elevator *elev, int order_type, int floor);

//Iterates through all elements of queue_matrix to see if any orders are active. Returns 0 if there are active orders in 
//the upwards direction, 1 to indicate stop, 2 to indicate active orders in downwards direction
int queue_active_orders(Elevator *elev);

//Returns direction of the next order to be treated
int queue_get_movement_direction(Elevator *elev);

//Returns the order type of the order which is to be treated
int queue_get_direction_of_order(Elevator *elev);

//Iterates through all elements of queue_matrix to see if any elements in the current direction is set to 1. Returns 1 if it is, 0 otherwise.
int queue_active_orders_in_current_direction(Elevator *elev);

//Returns true if there are any untreated orders at current floor, 0 otherwise
int queue_orders_current_floor(Elevator *elev);

#endif