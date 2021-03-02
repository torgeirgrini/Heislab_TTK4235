#include "elevator.h"
#include "utilities.h"

void init_elevator(Elevator *elev) {
    elev->queue_handler = queue_matrix_init(HARDWARE_NUMBER_OF_FLOORS);
    elev->current_floor = read_all_floor_sensors();
    elev->current_dir = HARDWARE_MOVEMENT_STOP;
    elev->current_state = INIT;
    elev->stop_light_set = 0;
    elev->timer_set = 0;
}

int elevator_opposite_dir(int current_dir) {
    if (current_dir == HARDWARE_MOVEMENT_UP) {return HARDWARE_MOVEMENT_DOWN;}
    if (current_dir == HARDWARE_MOVEMENT_DOWN) {return HARDWARE_MOVEMENT_UP;}
    return HARDWARE_MOVEMENT_STOP;
}