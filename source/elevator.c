#include "elevator.h"

void init_elevator(Elevator *elev) {
    elev->current_floor = read_all_floor_sensors();
    elev->current_dir = HARDWARE_MOVEMENT_STOP;
    elev->current_state = INIT;
    elev->stop_light_set = 0;
    elev->timer_set = 0;
    elev->current_order_dir = HARDWARE_MOVEMENT_STOP;
    elev->last_dir=HARDWARE_MOVEMENT_STOP;

    elev->queue_matrix = malloc(ELEVATOR_NUMBER_OF_ORDERS*sizeof(int*));
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS ; i++){
        elev->queue_matrix[i] = malloc(HARDWARE_NUMBER_OF_FLOORS*sizeof(int));
    }
    
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            elev->queue_matrix[i][j] = 0;
        }
    }

}