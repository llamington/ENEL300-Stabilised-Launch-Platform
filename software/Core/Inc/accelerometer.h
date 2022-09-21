#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_POTENTIOMETERS 3

typedef struct
{
    int8_t x, y, z;
} acceleration_t;

/**
 * @brief Initialise accelerometer
 */
void accelerometer_init(void);

void read_acceleration(acceleration_t *accel);

#endif