#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "timer.h"
#include "utilities.h"
#include "states.h"
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
    clear_all_order_lights();


    while(1) {
        printf("LD: %d\n", p_elevator->last_dir);
        printf("LOD: %d\n", p_elevator->current_order_dir);
        printf("CF: %d\n", p_elevator->current_floor);
        printf("CM: %d\n", p_elevator->current_movement);

        queue_set_orders(p_elevator);
        
        order_light_on(p_elevator);

        stop_signal_handler(p_elevator);
        
        switch(p_elevator->current_state) {

            case IDLE_IN_FLOOR:
                printf("ENTERED IDLE STATE\n");
                if(queue_orders_current_floor(p_elevator)) {
                    printf("DOOR OPENS IN IDLE");
                    p_elevator->current_state = DOOR_OPEN;
                }
                else if(queue_active_orders(p_elevator)) {
                    p_elevator->current_movement = queue_get_movement_direction(p_elevator);
                    p_elevator->current_state = MOVEMENT;
                }
                break;
                
            case IDLE_IN_SHAFT:
                printf("ENTERED IDLE IN SHAFT\n");
                
                if(queue_active_orders(p_elevator)) {
                    adjust_floor_after_stop(p_elevator);
                    p_elevator->current_movement = queue_get_movement_direction(p_elevator);
                    p_elevator->current_state = MOVEMENT;
                }
                break;

            case MOVEMENT:
                printf("ENTERED MOVEMENT STATE\n");

                hardware_command_movement(p_elevator->current_movement);
                
                update_floor(p_elevator);

                if(hardware_read_floor_sensor(p_elevator->current_floor) && queue_check_orders_current_floor(p_elevator)) { 
                    printf("DOOR OPENS");
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    p_elevator->last_dir = p_elevator->current_movement;
                    p_elevator->current_movement = HARDWARE_MOVEMENT_STOP;
                    p_elevator->current_state = DOOR_OPEN; 
                
                }
                break;

            case DOOR_OPEN:
                printf("ENTERED DOOR OPEN STATE\n");
                hardware_command_door_open(1);
                p_elevator->current_state = TIMER;
                break;

            case TIMER:
                printf("ENTERED TIMER STATE\n");
                if(!p_elevator->timer_set) {
                    before = timer_set();
                    p_elevator->timer_set = 1;
                }
                if(hardware_read_obstruction_signal()) {
                    before = timer_set();
                }
                if (timer_finished(before, 3000)) {
                    hardware_command_door_open(0);
                    p_elevator->current_order_dir = queue_get_direction_of_order(p_elevator);
                    for(int i = 0; i < ELEVATOR_NUMBER_OF_ORDERS; i++) {
                        queue_delete_order(p_elevator, i, p_elevator->current_floor);
                    }
                    p_elevator->timer_set = 0;
                    p_elevator->current_state = IDLE_IN_FLOOR;
                }
                    break;

            case STOP_BTN_SHAFT:
                printf("ENTERED STOP BTN SHAFT STATE\n");
                if(!p_elevator->stop_light_set) {
                    hardware_command_stop_light(1);
                    p_elevator->stop_light_set = 1;
                }
                queue_clear(p_elevator);
                if(!hardware_read_stop_signal()) {
                    hardware_command_stop_light(0);
                    p_elevator->stop_light_set = 0;
                    p_elevator->current_state = IDLE_IN_SHAFT;
                }
                break;

            case STOP_BTN_FLOOR:
                printf("ENTERED STOP BTN FLOOR STATE\n");
                if(!p_elevator->stop_light_set) {
                    hardware_command_stop_light(1);
                    p_elevator->stop_light_set = 1;
                    hardware_command_door_open(1);
                }
                queue_clear(p_elevator);
                if(!hardware_read_stop_signal()) {
                    hardware_command_stop_light(0);
                    p_elevator->stop_light_set = 0;
                    p_elevator->current_state = TIMER;
                }
                break;
        }

    }
    //deallocate memory

}
