#include "queue_handler.h"

int ** queue_matrix_init(int number_of_floors) {
    int **queue_matrix;
    queue_matrix = malloc(QUEUE_HANDLER_NUMBER_OF_ROWS*sizeof(int*));
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS ; i++){
        queue_matrix[i] = malloc(number_of_floors*sizeof(int));
    }

    queue_matrix_clear(queue_matrix, number_of_floors);

    return queue_matrix;
}

void queue_matrix_clear(int **queue_matrix, int number_of_floors) {
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < number_of_floors; j++) {
            queue_matrix[i][j] = 0;
        }
    }
}