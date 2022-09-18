#ifndef __PID_H
#define __PID_H

#include <stdint.h>
#include "tim.h"

/**
 * @brief Initialise the PID controller
 */
static inline void pid_init(void)
{
    HAL_TIM_Base_Start(&htim21);
}

/**
 * @brief Compute the PID control
 *
 * @param x: X-axis measurement
 * @param y: Y-axis measurement
 * @param servo_x: X-axis servo control
 * @param servo_y: Y-axis servo control
 */
void compute_control(int16_t x, int16_t y, uint16_t *servo_x, uint16_t *servo_y);

/**
 * @brief Sets the PID gains
 */
void set_gains(uint8_t k_p, uint8_t k_i, uint8_t k_d);

#endif