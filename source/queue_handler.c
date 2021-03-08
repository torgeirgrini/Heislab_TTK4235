#include "queue_handler.h"

void queue_matrix_clear(Elevator *elev) {
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            elev->queue_matrix[i][j] = 0;
        }
    }
}

int queue_matrix_active_orders(Elevator *elev) {
    int start_floor_search = 0;
    int end_floor_search = 0;
    int order_type = 0;
    
    //Elevators direction is up
    if (elev->current_order_dir == HARDWARE_MOVEMENT_UP) {
        start_floor_search = elev->current_floor+1;
        end_floor_search = HARDWARE_NUMBER_OF_FLOORS;
        order_type = HARDWARE_ORDER_UP;
        for(int j = start_floor_search; j < end_floor_search; j++) {
            if (elev->queue_matrix[order_type][j] || elev->queue_matrix[HARDWARE_ORDER_INSIDE][j]) {
                return HARDWARE_MOVEMENT_UP;
            }
        }
        if(queue_matrix_get_order(elev, HARDWARE_MOVEMENT_DOWN, end_floor_search-1)) {
            return HARDWARE_MOVEMENT_UP;
        }
    } 
    //Elevators direction is down
    else if (elev->current_order_dir == HARDWARE_MOVEMENT_DOWN) {
        start_floor_search = elev->current_floor-1;
        end_floor_search = 0;
        order_type = HARDWARE_ORDER_DOWN;
        //Check if the lowest floor is requesting to go up

        for(int j = start_floor_search; j == end_floor_search; j--) {
            if (elev->queue_matrix[order_type][j] || elev->queue_matrix[HARDWARE_ORDER_INSIDE][j]) {
                return HARDWARE_MOVEMENT_DOWN;
            }
        }
        if(queue_matrix_get_order(elev, HARDWARE_MOVEMENT_UP, end_floor_search)) {
            return HARDWARE_MOVEMENT_DOWN;
        }
    }
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            if (elev->queue_matrix[i][j]) {
                if (j > elev->current_floor) {
                    return HARDWARE_MOVEMENT_UP;
                }
                else if (j < elev->current_floor) {
                    return HARDWARE_MOVEMENT_DOWN;
                }
            }
        }
    }
    return HARDWARE_MOVEMENT_STOP;
}

int queue_matrix_get_order_dir(Elevator *elev) {
    if(queue_matrix_get_order(elev, elev->last_dir, elev->current_floor)) {
        return elev->last_dir;
    }
    else if(queue_matrix_get_order(elev, elevator_opposite_dir(elev->last_dir), elev->current_floor)) {
        return elevator_opposite_dir(elev->last_dir);
    }
    return HARDWARE_MOVEMENT_STOP;
}

int queue_matrix_active_orders_cur_dir(Elevator *elev) {
    printf("JA [%d]\n", elev->current_dir);
    
    if (elev->current_dir == HARDWARE_MOVEMENT_STOP) {
        return 0;
    }
    int start_floor_search = 0;
    int end_floor_search = 0;

    if (elev->current_floor == (HARDWARE_NUMBER_OF_FLOORS-1) || elev->current_floor == 0) {
        return 0;
    }
    //Elevators direction is up
    if (elev->current_dir == HARDWARE_MOVEMENT_UP) {
        start_floor_search = elev->current_floor+1;
        end_floor_search = HARDWARE_NUMBER_OF_FLOORS;
        //Check if the upper floor is requesting to go down
        if (queue_matrix_get_order(elev, HARDWARE_ORDER_DOWN, end_floor_search-1)) {
            return 1;
        }
    }
    //Elevators direction is down
    else if (elev->current_dir == HARDWARE_MOVEMENT_DOWN) {
        start_floor_search = 0;
        end_floor_search = elev->current_floor;
        //Check if the lowest floor is requesting to go up
        if(queue_matrix_get_order(elev, HARDWARE_ORDER_UP, start_floor_search)) {
            return 1;
        }
    }
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = start_floor_search; j < end_floor_search; j++) {
            if (queue_matrix_get_order(elev, i, j)) {
                return 1;
            }
        }
    }
    return 0;
}

void queue_matrix_update(Elevator *elev) {
    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            if(hardware_read_order(j, i)){
                elev->queue_matrix[i][j] = 1;
            }
        }
    }
}

int queue_matrix_get_order(Elevator *elev, int order_type, int floor) {
    return elev->queue_matrix[order_type][floor];
}

void queue_matrix_delete_order(Elevator *elev, int order_type, int floor) {
    elev->queue_matrix[order_type][floor] = 0;
}