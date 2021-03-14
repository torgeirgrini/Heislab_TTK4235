/**
* @file
* @brief Useful functions
*/
#ifndef UTILITIES_H
#define UTILITIES_H
#include "hardware.h"

/**
 * @brief Reads all 4 floor sensors
 * @return Current floor if elevator is in a floor, -1 if elevator is in the shaft, i.e none of the sensors are triggered
 */
int read_all_floor_sensors();

/**
 * @brief Clears all order lights
 */
void clear_all_order_lights();

/**
 * @brief Used for getting the opposite direction of @p direction
 * @param[in] direction Input direction
 * @return Opposite direction of @p direction
 */
HardwareMovement opposite_direction(HardwareMovement direction);


#endif
