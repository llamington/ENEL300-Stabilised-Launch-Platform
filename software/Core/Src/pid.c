#include <stdint.h>
#include "tim.h"
#include "stm32l0xx_hal_tim.h"

static int16_t last_x_err, last_y_err;
static uint8_t k_p, k_i, k_d;

void pid_compute(int16_t x, int16_t y, uint16_t *servo_x, uint16_t *servo_y)
{
    int16_t x_err = -x;
    int16_t y_err = -y;
    uint32_t timer_delta = __HAL_TIM_GET_COUNTER(&htim21);

    int32_t x_p_ctrl = k_p * x_err;
    int32_t y_p_ctrl = k_p * y_err;
    int32_t x_i_ctrl = k_i * last_x_err * timer_delta;
    int32_t y_i_ctrl = k_i * last_y_err * timer_delta;
    int32_t x_d_ctrl = k_d * (x_err - last_x_err) / timer_delta;
    int32_t y_d_ctrl = k_d * (y_err - last_y_err) / timer_delta;

    *servo_x = x_p_ctrl + x_i_ctrl + x_d_ctrl;
    *servo_y = y_p_ctrl + y_i_ctrl + y_d_ctrl;

    last_x_err = x_err;
    last_y_err = y_err;
    __HAL_TIM_GET_COUNTER(&htim21) = 0;
}