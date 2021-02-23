#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include <stdlib.h>

#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

//Returns a twodimensional array where each floor is a column. There are three rows. Row 0: Hall up, Row 1: Hall down, Row 2: Cab
int ** queue_matrix_init(int number_of_floors);

//Sets all elements of queue_matrix to zero.
void queue_matrix_clear(int **queue_matrix, int number_of_floors);


#endif