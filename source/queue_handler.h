/**
* @file
* @brief A library for doing operations with a queue matrix defined in an Elevator struct
*/ 
#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include "elevator.h"


#define QUEUE_HANDLER_NUMBER_OF_ROWS 3

/**
 * @brief Sets all elements of queue_matrix in an Elevator struct to zero.
 * 
 * @param[out] p_elev Pointer to an Elevator struct
 *
 */
void queue_clear(Elevator *p_elev);

/**
 * @brief Check a specified value in queue_matrix in an Elevator struct
 * 
 * @param[in] p_elev Pointer to an Elevator struct
 * @param[in] order_type The order type to check
 * @param[in] floor The floor to check
 * 
 * @return 1 if there is an unhandled order at @p floor with order type @p order_type in @p p_elev, 0 otherwise 
*/
int queue_get_order(Elevator *p_elev, HardwareOrder order_type, int floor);

/**
 * @brief Updates queue_matrix in an Elevator struct with new orders

 * @param[out] p_elev Pointer to an Elevator struct 
 */
void queue_set_orders(Elevator *p_elev);

/**
 * @brief Sets a specified value in queue_matrix in an Elevator struct to zero
 
 * @param[out] p_elev Pointer to an Elevator struct
 * @param[in] order_type The order type to nullify
 * @param[in] floor The floor to nullify
 */
void queue_delete_order(Elevator *p_elev, HardwareOrder order_type, int floor);

/**
 * @brief Checks a floor for any unhandled orders
 * 
 * @param[in] p_elev Pointer to an Elevator struct
 * @param[in] floor The floor to check
 * 
 * @returns 1 if there are any unhandled orders at the @p floor, 0 otherwise
 */
int queue_active_orders_floor(Elevator *p_elev, int floor);

/**
 * @brief Checks if there are any unhandled orders in an Elevator struct
 * 
 * @param[out] p_elev pointer to an Elevator struct
 * 
 * @return 1 if there are any unhandled orders in queue_matrix in @p p_elev
 */
int queue_active_orders_all_floors(Elevator *p_elev);

/**
 * @brief Checks for the direction for the elevator to move independent of priority
 * 
 * @param[in] p_elev pointer to an Elevator struct
 * 
 * @return the direction for the elevator that @p p_elev represents to move
 */
HardwareMovement queue_get_movement_any_direction(Elevator *p_elev);

//Returns direction of the next order to be treated
HardwareMovement queue_get_movement_direction(Elevator *p_elev);

//Returns the order type of the order which is to be treated
HardwareOrder queue_get_direction_of_order(Elevator *p_elev);

//Iterates through all elements of queue_matrix to see if any elements in the direction direction_type is set to 1. Returns 1 if it is, 0 otherwise.
int queue_active_orders_in_direction(Elevator *p_elev, HardwareMovement direction_type);

//Checks if any orders at the current floor are to be treated next
int queue_check_orders_current_floor(Elevator* p_elev);

#endif