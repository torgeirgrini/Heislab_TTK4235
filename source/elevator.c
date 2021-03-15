#include "elevator.h"

void elevator_init(Elevator *p_elev) {
    p_elev->current_floor = -1;
    p_elev->previous_floor = -1;
    p_elev->current_movement = HARDWARE_MOVEMENT_STOP;
    p_elev->current_state = INIT;
    p_elev->stop_light_set = 0;
    p_elev->timer_set = 0;
    p_elev->order_direction = HARDWARE_MOVEMENT_STOP;
    p_elev->previous_direction=HARDWARE_MOVEMENT_STOP;

    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            p_elev->queue_matrix[i][j] = 0;
        }
    }
}

void elevator_startup_routine(Elevator *p_elev) {
    while(read_all_floor_sensors() == -1) {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        p_elev->current_movement = HARDWARE_MOVEMENT_UP;
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    p_elev->previous_direction = HARDWARE_MOVEMENT_UP;
    p_elev->current_movement = HARDWARE_MOVEMENT_STOP;
    p_elev->current_state = IDLE_IN_FLOOR;
    elevator_update_floor(p_elev);
}

void elevator_set_order_light(Elevator *p_elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            hardware_command_order_light(j, i, p_elev->queue_matrix[i][j]);
        }
    }
}

void elevator_update_floor(Elevator *p_elev) {
    int floor_read = read_all_floor_sensors();
    if(floor_read != -1) {
        p_elev->previous_floor = p_elev->current_floor;
        p_elev->current_floor = floor_read;
        hardware_command_floor_indicator_on(p_elev->current_floor);
    }
}