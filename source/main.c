#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"
#include "states.h"

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
/*    
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
*/

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    
    int newval, oldval;
    newval = hardware_read_obstruction_signal(0);
    
    while(1){
        oldval = newval;
        newval = hardware_read_floor_sensor(0);

        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        /* Code block that makes the elevator go up when it reach the botton*/
        if(hardware_read_floor_sensor(0) && (newval > oldval)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            control_timer(3000);
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }

        /* Code block that makes the elevator go down when it reach the top floor*/
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }

        /* All buttons must be polled, like this: */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
        }

        /* Lights are set and cleared like this: */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            /* Internal orders */
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
            }

            /* Orders going up */
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            }

            /* Orders going down */
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
            }
        }

        /* Code to clear all lights given the obstruction signal */
        if(hardware_read_obstruction_signal()){
            hardware_command_stop_light(1);
            clear_all_order_lights();
        }
        else{
            hardware_command_stop_light(0);
        }
    }

    return 0;
}
