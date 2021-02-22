#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"
#include "states/states.h"

static void clear_all_order_lights(){
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


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
    state current_state = INIT;

    while(1) {
        switch(current_state) {
            case INIT:
                while(!read_all_floor_sensors()) {
                    hardware_command_movement(HARDWARE_MOVEMENT_UP);
                }
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                break;

            case IDLE_IN_FLOOR:
                //do something
                break;
            case IDLE_IN_SHAFT:
                //do something
                break;
            case MOVEMENT:
                //do something
                break;
            case DOOR_OPEN:
                //do something
                break;
            case TIMER:
                //do something
                break;
            case STOP_BTN_MOVEMENT:
                //do something
                break;
            case STOP_BTN_SHAFT:
                //do something
                break;
        }

    }

    return 0;
}
