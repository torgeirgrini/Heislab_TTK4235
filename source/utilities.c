#include "utilities.h"

int read_all_floor_sensors() {
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)) {return i;}
    }
    return -1;
}


HardwareMovement opposite_direction(HardwareMovement direction) {
    if (direction == HARDWARE_MOVEMENT_UP) {return HARDWARE_MOVEMENT_DOWN;}
    else if (direction == HARDWARE_MOVEMENT_DOWN) {return HARDWARE_MOVEMENT_UP;}
    return HARDWARE_MOVEMENT_STOP;
}