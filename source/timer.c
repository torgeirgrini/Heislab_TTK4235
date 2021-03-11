#include "timer.h"

clock_t timer_set() {
    return clock();
}

int timer_finished(clock_t previous_time, int timer_length_ms) {
    clock_t difference = (clock() - previous_time)*1000;
    int msec = difference / CLOCKS_PER_SEC;
    if (msec >= timer_length_ms) {
        return 1;
    }
    return 0;
}