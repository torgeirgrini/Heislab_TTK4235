/**
* @file
* @brief Library for stop button operations
*/

#ifndef STOP_BTN_H
#define STOP_BTN_H

#include "queue_handler.h"
/**
 * @brief Decides elevator behavior when stop button is pressed. 
 * If a floor sensor is activated the state of the elevator is to be set to STOP_BTN_FLOOR.
 * Otherwise the state of the elevator is to be set to STOP_BTN_SHAFT.
 * @param[in,out] p_elev Pointer to an Elevator struct 
 */
void stop_btn_handler(Elevator *p_elev);

/**
 * @brief Workaround for issue with movement after the stop button is released when in shaft. 
 * If there are no orders in the last direction and last direction is downwards, the current floor is decremented.
 * If there are no orders in the last direction and last direction is upwards, the current floor is incremented.
 * @param p_elev Pointer to an Elevator struct
 */

void stop_btn_adjust_floor(Elevator *p_elev);







#endif