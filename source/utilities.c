#include "utilities.h"

void control_timer(int milliseconds) {
    int timer_finished = 0;
    while(!timer_finished) {
        timer_finished = setTimer(milliseconds);
    }
}