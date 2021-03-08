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

    clock_t before;

    Elevator elevator_struct;
    Elevator *elevator_struct_ptr = &elevator_struct;
    init_elevator(elevator_struct_ptr);
    elevator_startup_routine(elevator_struct_ptr);
    elevator_struct.current_state = IDLE_IN_FLOOR;

    clear_all_order_lights();

    while(1) {


        queue_matrix_update(elevator_struct_ptr);
        
        //Turns on lights
        for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
            for(int j = 0; j < HARDWARE_NUMBER_OF_FLOORS; j++) {
                hardware_command_order_light(j, i, elevator_struct.queue_matrix[i][j]);
            }
        }

        switch(elevator_struct.current_state) {
            case IDLE_IN_FLOOR:
                printf("ENTERED IDLE STATE\n");
                //Check if anyone inside the elevator has requested to get off the elevator at this floor
                if(hardware_read_stop_signal()) {
                    elevator_struct.current_state = STOP_BTN_FLOOR;
                }
                printf("Current order direction %d\n", elevator_struct.current_order_dir);
                for(int i = 0; i < 3; i++) {
                    if(queue_matrix_get_order(elevator_struct_ptr, i, elevator_struct.current_floor)) {
                        elevator_struct.current_state = DOOR_OPEN;
                    }
                }
                elevator_struct.last_dir = elevator_struct.current_dir;
                elevator_struct.current_dir = queue_matrix_active_orders(elevator_struct_ptr);
                printf("Current elevator direction %d\n", elevator_struct.current_dir);
                if(elevator_struct.current_dir != HARDWARE_MOVEMENT_STOP) {
                    elevator_struct.current_state = MOVEMENT;
                }
                break;
                
            case IDLE_IN_SHAFT:
                printf("ENTERED IDLE IN SHAFT\n");
                if(hardware_read_stop_signal()) {
                    elevator_struct.current_state = STOP_BTN_SHAFT;
                }
                elevator_struct.last_dir = elevator_struct.current_dir;
                elevator_struct.current_dir = queue_matrix_active_orders(elevator_struct_ptr);
                if(elevator_struct.current_dir != HARDWARE_MOVEMENT_STOP) {
                    elevator_struct.current_state = MOVEMENT;
                }
                break;

            case MOVEMENT:
                //printf("ENTERED MOVEMENT STATE\n");
                if(hardware_read_stop_signal()) {
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    elevator_struct.last_dir = elevator_struct.current_dir;
                    elevator_struct.current_dir = HARDWARE_MOVEMENT_STOP;
                    elevator_struct.current_state = STOP_BTN_SHAFT;
                }

                hardware_command_movement(elevator_struct.current_dir);
                int floor_read = read_all_floor_sensors(); //denne funker bare hvis kun en bestilling siden den returnerer den første den finner fra 0te etasje
                if(floor_read != -1) {
                    elevator_struct.current_floor = floor_read;
                    hardware_command_floor_indicator_on(elevator_struct.current_floor);
                }

                if(hardware_read_floor_sensor(elevator_struct.current_floor)) { 
                    //Check if anyone inside the elevator has requested to get off the elevator at this floor
                    if(queue_matrix_get_order(elevator_struct_ptr, HARDWARE_ORDER_INSIDE, elevator_struct.current_floor)) {
                        printf("case 1\n");
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator_struct.last_dir = elevator_struct.current_dir;
                        elevator_struct.current_dir = HARDWARE_MOVEMENT_STOP;
                        elevator_struct.current_state = DOOR_OPEN;
                    }
                    
                    //if(elevator_struct.queue_matrix[elevator_struct.current_dir][elevator_struct.current_floor]) {
                    //Check if anyone outside the elevator has requested to step into the elevator in the current direction at this floor
                    else if(queue_matrix_get_order(elevator_struct_ptr, elevator_struct.current_dir, elevator_struct.current_floor)) {
                        printf("case 2\n");
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator_struct.last_dir = elevator_struct.current_dir;
                        elevator_struct.current_dir = HARDWARE_MOVEMENT_STOP;
                        elevator_struct.current_state = DOOR_OPEN;
                    }
                    //If there are no active orders in the current direction. Then look for active orders at the current floor in the other direction
                    else if(!queue_matrix_active_orders_cur_dir(elevator_struct_ptr)) {
                        printf("case 3\n");
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator_struct.last_dir = elevator_struct.current_dir;
                        elevator_struct.current_dir = HARDWARE_MOVEMENT_STOP;
                        elevator_struct.current_state = DOOR_OPEN; 
                    } 
                    
                    
                }
                break;

            case DOOR_OPEN:
                printf("ENTERED DOOR OPEN STATE\n");
                /*
                if(hardware_read_stop_signal()) {
                    elevator_struct.current_state = STOP_BTN_FLOOR;
                }
                */
                hardware_command_door_open(1);
                elevator_struct.current_state = TIMER;
                break;

            case TIMER:
                //printf("ENTERED TIMER STATE\n");
                if(hardware_read_stop_signal()) {
                    elevator_struct.current_state = STOP_BTN_FLOOR;
                }
                if(!elevator_struct.timer_set) {
                    before = set_timer();
                    elevator_struct.timer_set = 1;
                }
                if(hardware_read_obstruction_signal()) {
                    before = set_timer();
                }
                if (timer_finished(before, 3000)) {
                    hardware_command_door_open(0);
                    elevator_struct.current_order_dir = queue_matrix_get_order_dir(elevator_struct_ptr);
                    for(int i = 0; i < QUEUE_HANDLER_NUMBER_OF_ROWS; i++) {
                        queue_matrix_delete_order(elevator_struct_ptr, i, elevator_struct.current_floor);
                    }
                    elevator_struct.timer_set = 0;
                    elevator_struct.current_state = IDLE_IN_FLOOR;
                }
                    break;

            case STOP_BTN_SHAFT:
                printf("ENTERED STOP BTN SHAFT STATE\n");
                if(!elevator_struct.stop_light_set) {
                    hardware_command_stop_light(1);
                    elevator_struct.stop_light_set = 1;
                }
                queue_matrix_clear(elevator_struct_ptr);
                if(!hardware_read_stop_signal()) {
                    printf("STOP SIGNAL OFF");
                    hardware_command_stop_light(0);
                    elevator_struct.stop_light_set = 0;
                    elevator_struct.current_state = IDLE_IN_SHAFT;
                }
                break;

            case STOP_BTN_FLOOR:
                printf("ENTERED STOP BTN FLOOR STATE\n");
                if(!elevator_struct.stop_light_set) {
                    hardware_command_stop_light(1);
                    elevator_struct.stop_light_set = 1;
                    hardware_command_door_open(1);
                }
                queue_matrix_clear(elevator_struct_ptr);
                if(!hardware_read_stop_signal()) {
                    hardware_command_stop_light(0);
                    elevator_struct.stop_light_set = 0;
                    elevator_struct.current_state = TIMER;
                }
                break;
        }

    }
    //deallocate memory

}
