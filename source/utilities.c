#include "utilities.h"
#include "hardware.h"

/*
void control_timer(int milliseconds) {
    int timer_finished = 0;
    while(!timer_finished) {
        timer_finished = setTimer(milliseconds);
    }
}
*/

int read_all_floor_sensors() {
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)) {
            return i;   
        }
    }
}
