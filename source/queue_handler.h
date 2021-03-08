#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include <stdlib.h>
#include "hardware.h"
#include "utilities.h"
#include "elevator.h"
/*
struct Elevator {
    int **queue_handler;
};*/

#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

//Sets all elements of queue_matrix to zero.
void queue_matrix_clear(Elevator *elev);

//Iterates through all elements of queue_matrix to see if any orders are active. Returns 0 if there are active orders in 
//the upwards direction, 1 to indicate stop, 2 to indicate active orders in downwards direction
int queue_matrix_active_orders(Elevator *elev);

//Returns the order type of the order which is to be treated
int queue_matrix_get_order_dir(Elevator *elev);

//Iterates through all elements of queue_matrix to see if any elements in the current direction is set to 1. Returns 1 if it is, 0 otherwise.
int queue_matrix_active_orders_cur_dir(Elevator *elev);

//Updates queue_matrix with new orders
void queue_matrix_update(Elevator *elev);

//Returns 1 if there is and order at queue_matrix[order_type][floor]. 0 otherwise
int queue_matrix_get_order(Elevator *elev, int order_type, int floor);

//Deletes the order at location queue_matrix[order_type][floor]
void queue_matrix_delete_order(Elevator *elev, int order_type, int floor);

#endif