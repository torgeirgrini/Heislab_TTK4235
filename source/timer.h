#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/*
//Returns 1 if timer finished successfully. Return 0 if timer was disrupted.
int setTimer(int trigger_ms);
*/


//starts a timer. returns the original time of the timer
clock_t setTimer();

//Checks if timer set by setTimer() has surpassed trigger_ms. Returns 1 if it has, 0 otherwise.
int timerFinished(clock_t before, int trigger_ms);

#endif