#include "elevator.h"
#include "utilities.h"

void init_elevator(Elevator *elev) {
    elev->queue_handler = queue_matrix_init(HARDWARE_NUMBER_OF_FLOORS);
    elev->current_floor = read_all_floor_sensors();
    elev->current_dir = 1;
    elev->current_state = INIT;
}