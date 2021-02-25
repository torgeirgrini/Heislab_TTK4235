#include "timer.h"
/*
int setTimer(int trigger_ms) {
    int obstruction;

    int msec = 0;
    clock_t start_t, difference;

    start_t = clock();
    
    while (msec < trigger_ms) {
        obstruction = hardware_read_obstruction_signal();

        if(obstruction) {
            return 0;
        }

        difference = (clock() - start_t)*1000;
        msec = difference / CLOCKS_PER_SEC;
    }
    return 1;
}*/

clock_t setTimer() {
    return clock();
}

int timerFinished(clock_t before, int trigger_ms) {
    clock_t difference = (clock() - before)*1000;
    int msec = difference / CLOCKS_PER_SEC;
    printf("msec %d\n", msec);
    if (msec >= trigger_ms) {
        return 1;
    }
    return 0;
}