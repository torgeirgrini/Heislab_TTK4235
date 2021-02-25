#include "timer.h"

clock_t setTimer() {
    return clock();
}

int timerFinished(clock_t before, int trigger_ms) {
    clock_t difference = (clock() - before)*1000;
    int msec = difference / CLOCKS_PER_SEC;
    if (msec >= trigger_ms) {
        return 1;
    }
    return 0;
}