#include "utilities.h"
#include "hardware.h"

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

int elevator_opposite_dir(int current_dir) {
    if (current_dir == HARDWARE_MOVEMENT_UP) {return HARDWARE_MOVEMENT_DOWN;}
    if (current_dir == HARDWARE_MOVEMENT_DOWN) {return HARDWARE_MOVEMENT_UP;}
    return HARDWARE_MOVEMENT_STOP;
}