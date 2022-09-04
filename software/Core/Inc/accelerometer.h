#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

#include <stdint.h>
typedef struct
{
    int32_t x, y, z;
} acceleration_t;

/**
 * @brief Begin read of accelerometer's acceleration_data
 */
void begin_accelerometer_read(void);

/**
 * @brief Read the most recent acceleration data.
 * @param accel: Acceleration data structure
 */
void get_acceleration(acceleration_t *accel);

#endif