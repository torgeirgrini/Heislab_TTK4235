#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "timer.h"
#include "stop_btn.h"


int main(){

    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    clock_t timer_previous;
    Elevator elevator;
    Elevator *p_elevator = &elevator;
    elevator_init(p_elevator);
    elevator_startup_routine(p_elevator);

    while(1) {
        
        if(p_elevator->current_state != STOP_BTN_FLOOR && p_elevator->current_state != STOP_BTN_SHAFT) {
            queue_set_orders(p_elevator);
            elevator_set_order_light(p_elevator);
            stop_btn_handler(p_elevator);  
        }

        switch(p_elevator->current_state) {

            case IDLE_IN_FLOOR:
                if(queue_active_orders_floor(p_elevator, p_elevator->current_floor)) {
                    p_elevator->order_direction = queue_get_direction_of_order(p_elevator);
                    p_elevator->current_state = DOOR_OPEN;
                }
                else if(queue_active_orders_all_floors(p_elevator)) {
                    p_elevator->current_movement = queue_get_movement_pri_direction(p_elevator);
                    p_elevator->current_state = MOVEMENT;
                }
                break;
                
            case IDLE_IN_SHAFT:
                if(queue_active_orders_all_floors(p_elevator)) {
                    stop_btn_adjust_floor(p_elevator);
                    p_elevator->current_movement = queue_get_movement_pri_direction(p_elevator);
                    p_elevator->current_state = MOVEMENT;
                }
                break;

            case MOVEMENT:
                hardware_command_movement(p_elevator->current_movement);
                elevator_update_floor(p_elevator);

                if(hardware_read_floor_sensor(p_elevator->current_floor) && queue_check_orders_current_floor(p_elevator) && (p_elevator->current_floor != p_elevator->previous_floor)) { 
                    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                    p_elevator->previous_direction = p_elevator->current_movement;
                    p_elevator->current_movement = HARDWARE_MOVEMENT_STOP;
                    p_elevator->order_direction = queue_get_direction_of_order(p_elevator);
                    p_elevator->current_state = DOOR_OPEN;
                }
                break;

            case DOOR_OPEN:
                hardware_command_door_open(1);
                p_elevator->current_state = TIMER;
                break;

            case TIMER:
                queue_delete_orders_at_floor(p_elevator, p_elevator->current_floor);
                if(!p_elevator->timer_set) {
                    timer_previous = timer_set();
                    p_elevator->timer_set = 1;
                }
                if(hardware_read_obstruction_signal()) {
                    timer_previous = timer_set();
                }
                if (timer_finished(timer_previous, 3000)) {
                    hardware_command_door_open(0);
                    p_elevator->timer_set = 0;
                    p_elevator->current_state = IDLE_IN_FLOOR;
                }
                break;

            case STOP_BTN_SHAFT:
                if(!p_elevator->stop_light_set) {
                    hardware_command_stop_light(1);
                    p_elevator->stop_light_set = 1;
                }
                queue_clear(p_elevator);
                elevator_set_order_light(p_elevator);
                if(!hardware_read_stop_signal()) {
                    hardware_command_stop_light(0);
                    p_elevator->stop_light_set = 0;
                    p_elevator->current_state = IDLE_IN_SHAFT;
                }
                break;

            case STOP_BTN_FLOOR:
                if(!p_elevator->stop_light_set) {
                    hardware_command_stop_light(1);
                    p_elevator->stop_light_set = 1;
                    hardware_command_door_open(1);
                }
                queue_clear(p_elevator);
                elevator_set_order_light(p_elevator);
                if(!hardware_read_stop_signal()) {
                    hardware_command_stop_light(0);
                    p_elevator->stop_light_set = 0;
                    p_elevator->current_state = TIMER;
                }
                break;
        }
    }
}
