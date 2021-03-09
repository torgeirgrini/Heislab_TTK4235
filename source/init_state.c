#include "init_state.h"

void elevator_startup_routine(Elevator *elev) {
    while(read_all_floor_sensors() == -1) {
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        elev->current_movement = HARDWARE_MOVEMENT_UP;
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    elev->current_movement = HARDWARE_MOVEMENT_STOP;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
        if(hardware_read_floor_sensor(i)) {
            elev->current_floor = i;
        }
    }
    elev->last_dir = HARDWARE_MOVEMENT_UP;
    hardware_command_floor_indicator_on(elev->current_floor);
}
