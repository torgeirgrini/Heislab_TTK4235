#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include <stdlib.h>
#include "hardware.h"

#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

//Returns a twodimensional array where each floor is a column. There are three rows. Row 0: Hall up, Row 1: Hall down, Row 2: Cab
int ** queue_matrix_init(int number_of_floors);

//Sets all elements of queue_matrix to zero.
void queue_matrix_clear(int **queue_matrix, int number_of_floors);

//Iterates through all elements of queue_matrix to see if any orders are active. Returns 0 if there are active orders in 
//the upwards direction, 1 to indicate stop, 2 to indicate active orders in downwards direction
int queue_matrix_active_orders(int **queue_matrix, int number_of_floors, int current_floor);

//Iterates through all elements of queue_matrix to see if any elements in the current direction is set to 1. Returns 1 if it is, 0 otherwise.
int queue_matrix_active_orders_cur_dir(int **queue_matrix, int number_of_floors, int current_floor, int current_direction);

void queue_matrix_update(int **queue_matrix, int number_of_floors);

#endif