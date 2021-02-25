#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"
#include "states.h"
#include "init_state.h"
#include "queue_handler.h"




int main(){

    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
 
    Elevator elevator_struct;
    init_elevator(elevator_struct);

    while(1) {
        //update order
        switch(elevator_struct.current_state) {
            case INIT:
                elevator_startup_routine(elevator_struct);
                elevator_struct.current_floor = read_all_floor_sensors();
                elevator_struct.current_state = IDLE_IN_FLOOR;
                break;

            case IDLE_IN_FLOOR:
                //look for orders
                break;
                
            case IDLE_IN_SHAFT:
                //look for orders
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
                hardware_command_stop_light(1);
                queue_matrix_clear(elevator_struct.queue_handler, HARDWARE_NUMBER_OF_FLOORS);
                while(hardware_read_stop_signal()){
                    //reject orders
                }
                hardware_command_stop_light(0);
                elevator_struct.current_state = IDLE_IN_SHAFT;
                break;

            case STOP_BTN_SHAFT:
                hardware_command_stop_light(1);
                queue_matrix_clear(elevator_struct.queue_handler, HARDWARE_NUMBER_OF_FLOORS);
                hardware_command_door_open(1);
                while(hardware_read_stop_signal()) {
                    //reject orders
                }
                hardware_command_stop_light(0);
                elevator_struct.current_state = TIMER;
                break;
        }

    }

    //Initialise queue handler matrix
    int **g_queue_matrix = queue_matrix_init(HARDWARE_NUMBER_OF_FLOORS);

    //Print queue handler matrix
    for (int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for (int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            printf("%d ", g_queue_matrix[i][j]);
        }
        printf("\n");
    }


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
        if(hardware_read_floor_sensor(0)){
            clock_t before;
            if(newval > oldval) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                before = setTimer();
            }
            if(hardware_read_obstruction_signal()) {
                before = setTimer();
            }
            if (timerFinished(before, 3000)) {
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
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
