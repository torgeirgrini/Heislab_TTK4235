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
 * @brief Checks for the direction for the elevator to move, independent of priorities
 * 
 * @param[in] p_elev pointer to an Elevator struct
 * 
 * @return direction for the elevator @p p_elev to move without order priorities
 */
HardwareMovement queue_get_movement_any_direction(Elevator *p_elev);

/**
 * @brief Checks for the direction for the elevator to move, with priorities
 * 
 * @param[in] p_elev pointer to an Elevator struct
 * 
 * @return direction for the next order the elevator @p p_elev should handle
 */
HardwareMovement queue_get_movement_direction(Elevator *p_elev);

/**
 * @brief Checks the order type of the order just handled
 * 
 * @param[in] p_elev pointer an Elevator struct
 * 
 * @return the order type of the order which the elevator @p p_elev just handled
 */
HardwareOrder queue_get_direction_of_order(Elevator *p_elev);

/**
 * @brief Checks if there are any unhandled orders at the floors in which the @p direction_type specifies
 * 
 * @param[in] p_elev pointer to an Elevator struct
 * @param[in] direction_type direction that the search for orders should be done in
 * 
 * @return 1 if there are unhandled orders for the elevator @p p_elev in the direction of @p direction_type, 0 otherwise
 */
int queue_active_orders_in_direction(Elevator *p_elev, HardwareMovement direction_type);

/**
 * @brief Checks if there are any orders at the current floor of @p p_elev which are to be handled next
 * 
 * @param[in] p_elev pointer to an Elevator struct
 * 
 * @return 1 if there are orders to handle next at current floor of @p p_elev , 0 otherwise 
 */
int queue_check_orders_current_floor(Elevator* p_elev);

#endif