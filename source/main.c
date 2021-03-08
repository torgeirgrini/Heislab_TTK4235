#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"
#include "states.h"
#include "init_state.h"
#include "queue_handler.h"
#include "elevator.h"
#include <time.h>


int main(){

    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    clock_t before;

    Elevator elevator;
    Elevator *p_elevator = &elevator;
    init_elevator(p_elevator);
    elevator_startup_routine(p_elevator);
    elevator.current_state = IDLE_IN_FLOOR;
    clear_all_order_lights();

    while(1) {
        queue_set_orders(p_elevator);
        
        order_light_on(p_elevator);

        stop_signal_handler(p_elevator);
        
        switch(elevator.current_state) {
            case IDLE_IN_FLOOR:
                printf("ENTERED IDLE STATE\n");

                if(queue_orders_current_floor(p_elevator)) {
                    elevator.current_state = DOOR_OPEN;
                }

                if(queue_active_orders(p_elevator)) {
                    elevator.last_dir = elevator.current_dir;
                    elevator.current_dir = queue_active_orders(p_elevator);
                    elevator.current_state = MOVEMENT;
                }

                break;
                
            case IDLE_IN_SHAFT:
                printf("ENTERED IDLE IN SHAFT\n");
                if(queue_active_orders(p_elevator)) {
                    elevator.last_dir = elevator.current_dir;
                    elevator.current_dir = queue_active_orders(p_elevator);
                    elevator.current_state = MOVEMENT;
                }
                break;

            case MOVEMENT:
                //printf("ENTERED MOVEMENT STATE\n");

                hardware_command_movement(elevator.current_dir);
                
                update_floor(p_elevator);

                if(hardware_read_floor_sensor(elevator.current_floor)) { 
                    //Check if anyone inside the elevator has requested to get off the elevator at this floor
                    if(queue_get_order(p_elevator, HARDWARE_ORDER_INSIDE, elevator.current_floor)) {
                        printf("case 1\n");
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator.last_dir = elevator.current_dir;
                        elevator.current_dir = HARDWARE_MOVEMENT_STOP;
                        elevator.current_state = DOOR_OPEN;
                    }
                    
                    //Check if anyone outside the elevator has requested to step into the elevator in the current direction at this floor
                    else if(queue_get_order(p_elevator, elevator.current_dir, elevator.current_floor)) {
                        printf("case 2\n");
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator.last_dir = elevator.current_dir;
                        elevator.current_dir = HARDWARE_MOVEMENT_STOP;
                        elevator.current_state = DOOR_OPEN;
                    }
                    //If there are no active orders in the current direction. Then there must be a active order on the current floor in the opposite direction
                    else if(!queue_active_orders_in_current_direction(p_elevator)) {
                        printf("case 3\n");
                        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                        elevator.last_dir = elevator.current_dir;
                        elevator.current_dir = HARDWARE_MOVEMENT_STOP;
                        elevator.current_state = DOOR_OPEN; 
                    } 
                }
                break;

            case DOOR_OPEN:
                printf("ENTERED DOOR OPEN STATE\n");
                hardware_command_door_open(1);
                elevator.current_state = TIMER;
                break;

            case TIMER:
                //printf("ENTERED TIMER STATE\n");
                if(!elevator.timer_set) {
                    before = timer_set();
                    elevator.timer_set = 1;
                }
                if(hardware_read_obstruction_signal()) {
                    before = timer_set();
                }
                if (timer_finished(before, 3000)) {
                    hardware_command_door_open(0);
                    elevator.current_order_dir = queue_get_direction_of_order(p_elevator);
                    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
                        queue_delete_order(p_elevator, i, elevator.current_floor);
                    }
                    elevator.timer_set = 0;
                    elevator.current_state = IDLE_IN_FLOOR;
                }
                    break;

            case STOP_BTN_SHAFT:
                printf("ENTERED STOP BTN SHAFT STATE\n");
                if(!elevator.stop_light_set) {
                    hardware_command_stop_light(1);
                    elevator.stop_light_set = 1;
                }
                queue_clear(p_elevator);
                if(!hardware_read_stop_signal()) {
                    printf("STOP SIGNAL OFF");
                    hardware_command_stop_light(0);
                    elevator.stop_light_set = 0;
                    elevator.current_state = IDLE_IN_SHAFT;
                }
                break;

            case STOP_BTN_FLOOR:
                printf("ENTERED STOP BTN FLOOR STATE\n");
                if(!elevator.stop_light_set) {
                    hardware_command_stop_light(1);
                    elevator.stop_light_set = 1;
                    hardware_command_door_open(1);
                }
                queue_clear(p_elevator);
                if(!hardware_read_stop_signal()) {
                    hardware_command_stop_light(0);
                    elevator.stop_light_set = 0;
                    elevator.current_state = TIMER;
                }
                break;
        }

    }
    //deallocate memory

}
