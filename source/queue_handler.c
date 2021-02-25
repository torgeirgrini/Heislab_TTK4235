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

int queue_matrix_active_order(int **queue_matrix, int number_of_floors, int current_floor) {
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < number_of_floors; j++) {
            if (queue_matrix[i][j]) {
                if (j < current_floor) {
                    return 2;
                }
                else if (j > current_floor) {
                    return 0;
                }
            }
        }
    }
}

int queue_matrix_active_orders_cur_dir(int **queue_matrix, int number_of_floors, int current_floor, int current_direction) {
    if (current_direction == 1) {return 0;}

    if (current_floor == (number_of_floors-1) || current_floor == 0) {
        return 0;
    }
    int start_floor_search = 0;
    int end_floor_search = 0;
    int check_command = 0;
    int inside_hall = 2;
    
    //Elevators direction is up
    if (current_direction == 0) {
        start_floor_search = current_floor+1;
        end_floor_search = number_of_floors-1;
        check_command = 0;
        //Check if the upper floor is requesting to go down
        if (queue_matrix[1][end_floor_search]) {return 1;}
    } 
    //Elevators direction is down
    else if (current_direction == 2) {
        int start_floor_search = 0;
        int end_floor_search = current_floor-1;
        int check_command = 1;
        //Check if the lowest floor is requesting to go up
        if (queue_matrix[0][start_floor_search]) {return 1;}
    }
    
    for(int j = start_floor_search; j < number_of_floors; j++) {
        if (queue_matrix[check_command][j] || queue_matrix[inside_hall][j]) {
            return 1;
        }
    }
}

void queue_matrix_update(int **queue_matrix, int number_of_floors) {
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < number_of_floors; j++) {
            if(hardware_read_order(j, i)){
                queue_matrix[i][j] = 1;
            }
        }
    }
}