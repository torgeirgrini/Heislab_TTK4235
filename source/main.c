#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"
#include "states.h"
#include "init_state.h"
#include "queue_handler.h"
#include "time.h"
#include "elevator.h"
#include "idle_state.h"





int main(){

    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    int timerSet = 0;
    clock_t before;

    Elevator elevator_struct;
    Elevator *elevator_struct_ptr = &elevator_struct;
    init_elevator(elevator_struct_ptr);
    elevator_startup_routine(elevator_struct_ptr);
    elevator_struct.current_state = IDLE_IN_FLOOR;
    printf("\nCurrent floor %d\n", elevator_struct.current_floor);

    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
        for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
            printf(" %d", elevator_struct.queue_handler[i][j]);
        }
    }

    while(1) {

        queue_matrix_update(elevator_struct.queue_handler, HARDWARE_NUMBER_OF_FLOORS);
        switch(elevator_struct.current_state) {

            case IDLE_IN_FLOOR:
                printf("ENTERED IDLE STATE\n");
                elevator_struct.current_dir = queue_matrix_active_orders(elevator_struct.queue_handler, HARDWARE_NUMBER_OF_FLOORS, elevator_struct.current_floor);
                if(elevator_struct.current_dir != 1) {
                    elevator_struct.current_state = MOVEMENT;
                }
                break;
                
            case IDLE_IN_SHAFT:
                printf("ENTERED IDLE IN SHAFT\n");
                //look for orders
                break;

            case MOVEMENT:
                //printf("ENTERED MOVEMENT STATE\n");
                
                hardware_command_movement(elevator_struct.current_dir);
                int floor_read = read_all_floor_sensors();
                if(floor_read != -1) {
                    elevator_struct.current_floor = floor_read;
                }
                if(hardware_read_floor_sensor(elevator_struct.current_floor)) {
                    if(elevator_struct.queue_handler[elevator_struct.current_dir][elevator_struct.current_floor]) {
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator_struct.current_state = DOOR_OPEN;
                    }            
                }
                break;

            case DOOR_OPEN:
                printf("ENTERED DOOR OPEN STATE\n");
                hardware_command_door_open(1);
                elevator_struct.current_state = TIMER;
                break;

            case TIMER:
                printf("ENTERED TIMER STATE\n");
                if(!timerSet) {
                    before = setTimer();
                    timerSet = 1;
                }
                if(hardware_read_obstruction_signal()) {
                    before = setTimer();
                }
                if (timerFinished(before, 3000)) {
                    hardware_command_door_open(0);
                    elevator_struct.current_state = IDLE_IN_FLOOR;
                    timerSet = 0;
                }
                    break;

            case STOP_BTN_MOVEMENT:
                printf("ENTERED STOP BTN MOVEMENT STATE\n");
                hardware_command_stop_light(1);
                queue_matrix_clear(elevator_struct.queue_handler, HARDWARE_NUMBER_OF_FLOORS);
                while(hardware_read_stop_signal()){
                    //reject orders
                }
                hardware_command_stop_light(0);
                elevator_struct.current_state = IDLE_IN_SHAFT;
                break;

            case STOP_BTN_SHAFT:
                printf("ENTERED STOP BTN SHAFT STATE\n");
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

}
