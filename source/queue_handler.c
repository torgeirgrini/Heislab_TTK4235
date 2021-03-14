#include "queue_handler.h"

void queue_clear(Elevator *p_elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            p_elev->queue_matrix[i][j] = 0;
        }
    }
}

int queue_get_order(Elevator *p_elev, HardwareOrder order_type, int floor) {
    return p_elev->queue_matrix[order_type][floor];
}

void queue_set_orders(Elevator *p_elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            if(hardware_read_order(j, i)){
                p_elev->queue_matrix[i][j] = 1;
            }
        }
    }
}

void queue_delete_order(Elevator *p_elev, HardwareOrder order_type, int floor) {
    p_elev->queue_matrix[order_type][floor] = 0;
}

int queue_active_orders_floor(Elevator *p_elev, int floor) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        if(queue_get_order(p_elev, i, floor)) {return 1;}
    }
    return 0;
}

int queue_active_orders_all_floors(Elevator *p_elev) {
    for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
        if (queue_active_orders_floor(p_elev, j)) {return 1;}
    }
    return 0;
}

HardwareMovement queue_get_movement_any_direction(Elevator *p_elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            if (p_elev->queue_matrix[i][j]) {
                if (j > p_elev->current_floor) {
                    return HARDWARE_MOVEMENT_UP;
                }
                else if (j < p_elev->current_floor) {
                    return HARDWARE_MOVEMENT_DOWN;
                }
            }
        }
    }
    return HARDWARE_MOVEMENT_STOP;
}


HardwareMovement queue_get_movement_direction(Elevator *p_elev) {
    int start_floor_search = 0;
    int end_floor_search = 0;
    if(queue_active_orders_floor(p_elev, p_elev->current_floor)) {return HARDWARE_MOVEMENT_STOP;}

    switch (p_elev->order_direction){
    case HARDWARE_MOVEMENT_UP:

        start_floor_search = p_elev->current_floor+1;
        end_floor_search = HARDWARE_NUMBER_OF_FLOORS;
        if(p_elev->current_floor == HARDWARE_NUMBER_OF_FLOORS-1) {return HARDWARE_MOVEMENT_DOWN;}
        for(int j = start_floor_search; j < end_floor_search; j++) {
            if (p_elev->queue_matrix[HARDWARE_ORDER_UP][j] || p_elev->queue_matrix[HARDWARE_ORDER_INSIDE][j]) {return HARDWARE_MOVEMENT_UP;}
        }
        break;
    
    case HARDWARE_MOVEMENT_DOWN:

        start_floor_search = p_elev->current_floor-1;
        end_floor_search = 0;
        if(p_elev->current_floor == 0) {return HARDWARE_MOVEMENT_UP;}
        for(int j = start_floor_search; j == end_floor_search; j--) {
            if (p_elev->queue_matrix[HARDWARE_ORDER_DOWN][j] || p_elev->queue_matrix[HARDWARE_ORDER_INSIDE][j]) {return HARDWARE_MOVEMENT_DOWN;}
        }
        break;
    }
    return queue_get_movement_any_direction(p_elev);
}

HardwareOrder queue_get_direction_of_order(Elevator *p_elev) {

    if(queue_get_order(p_elev, p_elev->previous_direction, p_elev->current_floor)) {return p_elev->previous_direction;}
    else if(queue_get_order(p_elev, opposite_direction(p_elev->previous_direction), p_elev->current_floor)) {return opposite_direction(p_elev->previous_direction);}

    return HARDWARE_MOVEMENT_STOP;
}

int queue_active_orders_in_direction(Elevator *p_elev, HardwareMovement direction_type) {

    int start_floor_search = 0;
    int end_floor_search = 0;

    if (direction_type == HARDWARE_MOVEMENT_UP) {
        start_floor_search = p_elev->current_floor+1;
        end_floor_search = HARDWARE_NUMBER_OF_FLOORS;
        if (p_elev->current_floor == HARDWARE_NUMBER_OF_FLOORS-1) {return 0;}        
    }
    else if (direction_type == HARDWARE_MOVEMENT_DOWN) {
        start_floor_search = 0;
        end_floor_search = p_elev->current_floor;
        if(p_elev->current_floor == 0) {return 0;}
    }
    for(int i = start_floor_search; i < end_floor_search; i++) {
        if (queue_active_orders_floor(p_elev, i)) {return 1;}
    }
    return 0;
}


int queue_check_orders_current_floor(Elevator* p_elev) {
    return (queue_get_order(p_elev, HARDWARE_ORDER_INSIDE, p_elev->current_floor)
    || queue_get_order(p_elev, p_elev->current_movement, p_elev->current_floor)
    || !queue_active_orders_in_direction(p_elev, p_elev->current_movement));
}
