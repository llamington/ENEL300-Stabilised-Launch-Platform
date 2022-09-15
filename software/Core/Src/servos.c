#include <stdint.h>
#include "stm32l0xx_hal.h"
#include "tim.h"
#include "servos.h"
#include "util.h"

#define SERVO_X_CHANNEL TIM_CHANNEL_1
#define SERVO_Y_CHANNEL TIM_CHANNEL_2
#define SERVO_PWM_PERIOD 53333 // Period of 20 ms

void servos_init(void)
{
    HAL_TIM_PWM_Start(&htim2, SERVO_X_CHANNEL);
    HAL_TIM_PWM_Start(&htim2, SERVO_Y_CHANNEL);
}

void set_servos_duty(uint16_t servo_x_duty, uint16_t servo_y_duty)
{
    servo_x_duty = BOUND(SERVO_PULSE_MIN, SERVO_PULSE_MAX, servo_x_duty);
    servo_y_duty = BOUND(SERVO_PULSE_MIN, SERVO_PULSE_MAX, servo_y_duty);
    __HAL_TIM_SET_COMPARE(&htim2, SERVO_X_CHANNEL, servo_x_duty);
    __HAL_TIM_SET_COMPARE(&htim2, SERVO_Y_CHANNEL, servo_y_duty);
}