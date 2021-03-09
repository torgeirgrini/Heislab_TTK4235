#include "utilities.h"

int read_all_floor_sensors() {
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)) {
            return i;   
        }
    }
    return -1;
}

void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

int opposite_direction(int current_dir) {
    if (current_dir == HARDWARE_MOVEMENT_UP) {return HARDWARE_MOVEMENT_DOWN;}
    if (current_dir == HARDWARE_MOVEMENT_DOWN) {return HARDWARE_MOVEMENT_UP;}
    return HARDWARE_MOVEMENT_STOP;
}

void order_light_on(Elevator *elev) {
    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            hardware_command_order_light(j, i, queue_get_order(elev, i, j));
        }
    }
}

void stop_signal_handler(Elevator *elev) {
    if(hardware_read_stop_signal() && (read_all_floor_sensors() != -1)) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        elev->current_state = STOP_BTN_FLOOR;
    }
    else if(hardware_read_stop_signal()) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        elev->last_dir = elev->current_movement;
        //elev->current_floor = -1;
        elev->current_movement = HARDWARE_MOVEMENT_STOP;
        elev->current_state = STOP_BTN_SHAFT;
    }
}

void update_floor(Elevator *elev) {
    int floor_read = read_all_floor_sensors();
    if(floor_read != -1) {
        elev->current_floor = floor_read;
        hardware_command_floor_indicator_on(elev->current_floor);
    }
}

