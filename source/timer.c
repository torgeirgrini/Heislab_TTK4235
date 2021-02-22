#include "timer.h"

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
}