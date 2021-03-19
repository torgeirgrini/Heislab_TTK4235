/**
* @file
* @brief Enum containing the states of the elevator
*/

#ifndef STATES_H
#define STATES_H

/**
 * @enum state Enum
 */

typedef enum state {
    INITIALIZE, /**<State for initialization*/
    IDLE_IN_FLOOR, /**<Elevator is idle in a floor*/
    IDLE_IN_SHAFT, /**<Elevator is idle in the shaft*/
    MOVEMENT, /**<Elevator is moving*/
    DOOR_OPEN, /**<Intermediate state for opening the door*/
    TIMER, /**<Door timer is active*/
    STOP_BTN_SHAFT, /**<Stop button has been pressed when elevator is in the shaft*/
    STOP_BTN_FLOOR /**<Stop button has been pressed when elevator is in a floor*/
} state;


#endif
