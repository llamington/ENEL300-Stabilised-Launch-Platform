#ifndef __PID_H
#define __PID_H

#include <stdint.h>
#include "tim.h"
#include "reduced_hal.h"

/**
 * @brief Initialise the PID controller
 */
static inline void pid_init(void)
{
    tim_base_start(&htim21);
}

/**
 * @brief Compute the PID control
 *
 * @param x: X-axis measurement
 * @param y: Y-axis measurement
 * @param servo_x: X-axis servo control
 * @param servo_y: Y-axis servo control
 */
void compute_control(int8_t x,
                     int8_t y,
                     uint16_t *servo_x,
                     uint16_t *servo_y,
                     uint8_t k_p,
                     uint8_t k_i,
                     uint8_t k_d);

/**
 * @brief Sets the PID gains
 */
// void set_gains(uint8_t k_p, uint8_t k_i, uint8_t k_d);

#endif