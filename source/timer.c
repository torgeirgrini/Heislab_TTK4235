#include "timer.h"

clock_t timer_set() {
    return clock();
}

int timer_finished(clock_t before, int trigger_ms) {
    clock_t difference = (clock() - before)*1000;
    int msec = difference / 10000;
    if (msec >= trigger_ms) {
        return 1;
    }
    return 0;
}