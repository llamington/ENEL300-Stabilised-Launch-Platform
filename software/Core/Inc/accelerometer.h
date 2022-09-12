#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_POTENTIOMETERS 3

typedef struct
{
    int16_t x, y, z;
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

/**
 * @brief Returns whether the acceleration data is ready to read
 */
bool accelerometer_read_ready(void);

/**
 * @brief Enables accelerometer data to be read
 */
void notify_accelerometer_read_ready(void);

#endif