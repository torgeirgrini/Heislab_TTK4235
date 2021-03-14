/**
* @file
* @brief Library containing the state enum
*/

#ifndef STATES_H
#define STATES_H

/**
 * @enum Enum containing all states
 */

typedef enum state {
    INIT, /**<State for initialization*/
    IDLE_IN_FLOOR, /**<Elevator is idle in a floor*/
    IDLE_IN_SHAFT, /**<Elevator is idle in the shaft*/
    MOVEMENT, /**<Elevator is moving between floors*/
    DOOR_OPEN, /**<Intermediate state for opening the door*/
    TIMER, /**<Door timer is active*/
    STOP_BTN_SHAFT, /**<Stop button has been pressed when elevator is in the shaft*/
    STOP_BTN_FLOOR /**<Stop button has been pressed when elevator is in a floor*/
} state;


#endif
