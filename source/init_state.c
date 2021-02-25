#include "init_state.h"

void elevator_startup_routine(Elevator elev) {
    while(!read_all_floor_sensors()) {
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                    elev.current_dir = HARDWARE_MOVEMENT_UP;
                }
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}
