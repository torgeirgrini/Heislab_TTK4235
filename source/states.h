/**
* @file
* @brief Header file containing the state enum
*/

#ifndef STATES_H
#define STATES_H

/**
 * @enum Enum containing all 
 */

typedef enum state {
    INIT, IDLE_IN_FLOOR, IDLE_IN_SHAFT, MOVEMENT, DOOR_OPEN, TIMER, STOP_BTN_SHAFT, STOP_BTN_FLOOR
} state;

#endif
