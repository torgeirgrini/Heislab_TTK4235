#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include <stdlib.h>
#include "hardware.h"
#include "utilities.h"

#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

//Returns a twodimensional array where each floor is a column. There are three rows. Row 0: Hall up, Row 1: Cab, Row 2: Hall down
int ** queue_matrix_init(int number_of_floors);

//Sets all elements of queue_matrix to zero.
void queue_matrix_clear(int **queue_matrix, int number_of_floors);

//Iterates through all elements of queue_matrix to see if any orders are active. Returns 0 if there are active orders in 
//the upwards direction, 1 to indicate stop, 2 to indicate active orders in downwards direction
int queue_matrix_active_orders(int **queue_matrix, int number_of_floors, int current_floor, int current_order_dir);

//Returns the order type of the order which is to be treated
int queue_matrix_get_order_dir(int **queue_matrix, int number_of_floors, int current_floor, int current_direction, int last_dir);

//Iterates through all elements of queue_matrix to see if any elements in the current direction is set to 1. Returns 1 if it is, 0 otherwise.
int queue_matrix_active_orders_cur_dir(int **queue_matrix, int number_of_floors, int current_floor, int current_direction);

//Updates queue_matrix with new orders
void queue_matrix_update(int **queue_matrix, int number_of_floors);

//Returns 1 if there is and order at queue_matrix[order_type][floor]. 0 otherwise
int queue_matrix_get_order(int **queue_matrix, int order_type, int floor);

//Deletes the order at location queue_matrix[order_type][floor]
void queue_matrix_delete_order(int **queue_matrix, int order_type, int floor);

#endif