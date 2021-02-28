#ifndef TIMER_H
#define TIMER_H

#include <time.h>

//starts a timer. returns the original time of the timer
clock_t set_timer();

//Checks if timer set by setTimer() has surpassed trigger_ms. Returns 1 if it has, 0 otherwise.
int timer_finished(clock_t before, int trigger_ms);

#endif