#include "queue_handler.h"

void queue_clear(Elevator *elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            elev->queue_matrix[i][j] = 0;
        }
    }
}

int queue_get_order(Elevator *elev, int order_type, int floor) {
    return elev->queue_matrix[order_type][floor];
}

void queue_delete_order(Elevator *elev, int order_type, int floor) {
    elev->queue_matrix[order_type][floor] = 0;
}

int queue_orders_current_floor(Elevator *elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        if(queue_get_order(elev, i, elev->current_floor)) {
            return 1;
        }
    }
    return 0;
}

int queue_active_orders(Elevator *elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            if (elev->queue_matrix[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

void queue_set_orders(Elevator *elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            if(hardware_read_order(j, i)){
                elev->queue_matrix[i][j] = 1;
            }
        }
    }
}

int queue_get_movement_direction(Elevator *elev) {
    int start_floor_search = 0;
    int end_floor_search = 0;

    if(queue_orders_current_floor(elev)) {
        return HARDWARE_MOVEMENT_STOP;
    }

    if (elev->current_order_dir == HARDWARE_MOVEMENT_UP) {
        start_floor_search = elev->current_floor+1;
        end_floor_search = HARDWARE_NUMBER_OF_FLOORS;
        if(elev->current_floor == HARDWARE_NUMBER_OF_FLOORS-1) {
            return HARDWARE_MOVEMENT_DOWN;
        }
        for(int j = start_floor_search; j < end_floor_search; j++) {
            if (elev->queue_matrix[HARDWARE_ORDER_UP][j] || elev->queue_matrix[HARDWARE_ORDER_INSIDE][j]) {
                return HARDWARE_MOVEMENT_UP;
            }
        }
    } 
    //Elevators direction is down
    else if (elev->current_order_dir == HARDWARE_MOVEMENT_DOWN) {
        start_floor_search = elev->current_floor-1;
        end_floor_search = 0;
        if(elev->current_floor == 0) {
            return HARDWARE_MOVEMENT_UP;
        }
        for(int j = start_floor_search; j == end_floor_search; j--) {
            if (elev->queue_matrix[HARDWARE_ORDER_DOWN][j] || elev->queue_matrix[HARDWARE_ORDER_INSIDE][j]) {
                return HARDWARE_MOVEMENT_DOWN;
            }
        }
    }
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
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

int queue_get_direction_of_order(Elevator *elev) {
    if(queue_get_order(elev, elev->last_dir, elev->current_floor)) {
        return elev->last_dir;
    }
    else if(queue_get_order(elev, opposite_direction(elev->last_dir), elev->current_floor)) {
        return opposite_direction(elev->last_dir);
    }
    else if(queue_get_order(elev, HARDWARE_MOVEMENT_UP, elev->current_floor)) {
        return HARDWARE_ORDER_UP;
    }
    else if(queue_get_order(elev, HARDWARE_MOVEMENT_DOWN, elev->current_floor)) {
        return HARDWARE_ORDER_DOWN;
    }
    return HARDWARE_MOVEMENT_STOP;
}

int queue_active_orders_in_current_direction(Elevator *elev) {
    int start_floor_search = 0;
    int end_floor_search = 0;

    if (elev->current_dir == HARDWARE_MOVEMENT_UP) {
        start_floor_search = elev->current_floor+1;
        end_floor_search = HARDWARE_NUMBER_OF_FLOORS;
        if (elev->current_floor == HARDWARE_NUMBER_OF_FLOORS-1) {
            return 0;
        }        
    }
    
    else if (elev->current_dir == HARDWARE_MOVEMENT_DOWN) {
        start_floor_search = 0;
        end_floor_search = elev->current_floor;
        if(elev->current_floor == 0) {
            return 0;
        }
    }

    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = start_floor_search; j < end_floor_search; j++) {
            if (queue_get_order(elev, i, j)) {
                return 1;
            }
        }
    }
    return 0;
}
