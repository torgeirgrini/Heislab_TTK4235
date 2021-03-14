/**
* @file
* @brief Library for timer operations
*/
#ifndef TIMER_H
#define TIMER_H
#include <time.h>

/**
 * @brief Starts a timer
 * @return Time used by the program so far (user time + system time)
 */
clock_t timer_set();

/** 
 * @brief Checks if the timer has surpassed @p timer_length_ms
 * @param[in] previous_time Reference time to compare current time with
 * @param[in] timer_length_ms Timer length in milliseconds
 * @return 1 if the timer is greater than @p timer_length_ms, 0 otherwise
 */
int timer_finished(clock_t previous_time, int timer_length_ms);

#endif