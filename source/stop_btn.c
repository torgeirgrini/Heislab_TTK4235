#include "stop_btn.h"


void stop_btn_handler(Elevator *p_elev) {
    if(hardware_read_stop_signal() && (read_all_floor_sensors() != -1)) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        p_elev->current_state = STOP_BTN_FLOOR;
    }
    else if(hardware_read_stop_signal()) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        if (p_elev->current_movement != HARDWARE_MOVEMENT_STOP) {
            p_elev->last_dir = p_elev->current_movement;
        }
        p_elev->current_movement = HARDWARE_MOVEMENT_STOP;
        p_elev->current_state = STOP_BTN_SHAFT;
    }
}

void stop_btn_adjust_floor(Elevator *p_elev) {
    if(!queue_active_orders_in_direction(p_elev, p_elev->last_dir) && (p_elev->last_dir == HARDWARE_MOVEMENT_DOWN)) {
        p_elev->current_floor--;
    }
    else if(!queue_active_orders_in_direction(p_elev, p_elev->last_dir) && (p_elev->last_dir == HARDWARE_MOVEMENT_UP)) {
        p_elev->current_floor++;
    } 
}


