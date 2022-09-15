#ifndef __SERVOS_H
#define __SERVOS_H

#include <stdint.h>

#define SERVO_PULSE_MIN 2667
#define SERVO_PULSE_MAX 5334
#define SERVO_PULSE_MED ((SERVO_PULSE_MAX + SERVO_PULSE_MIN) / 2)

/**
 * @brief Initialise the servo motors
 */
void servos_init(void);

/**
 * @brief Set the duty cycle of the servo motors
 * @param servo_x_duty: Duty cycle of X axis servo in terms of PWM clock ticks
 * @param servo_y_duty: Duty cycle of Y axis servo in terms of PWM clock ticks
 */
void set_servos_duty(uint16_t servo_x_duty, uint16_t servo_y_duty);

#endif