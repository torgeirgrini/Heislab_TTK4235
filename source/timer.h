#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include "hardware.h"

//Returns 1 if timer finished successfully. Return 0 if timer was disrupted.
int setTimer(int trigger_ms);

#endif