#include <stdint.h>
#include "tim.h"
#include "servos.h"
#include "stm32l0xx_hal_tim.h"

#define P_CTRL_DIV 75
#define I_CTRL_DIV 60000
#define D_CTRL_MUL 8

void compute_control(int8_t x,
                     int8_t y,
                     uint16_t *servo_x,
                     uint16_t *servo_y,
                     uint8_t k_p,
                     uint8_t k_i,
                     uint8_t k_d)
{
    static int16_t last_x_err = 0;
    static int16_t last_y_err = 0;
    static int32_t integral_x_err = 0;
    static int32_t integral_y_err = 0;

    int16_t x_err = -x;
    int16_t y_err = -y;
    uint32_t timer_delta = __HAL_TIM_GET_COUNTER(&htim21);

    integral_x_err += last_x_err * (int64_t)timer_delta;
    integral_y_err += last_y_err * (int64_t)timer_delta;

    int32_t x_p_ctrl = (int16_t)k_p * x_err / P_CTRL_DIV;
    int32_t y_p_ctrl = (int16_t)k_p * y_err / P_CTRL_DIV;
    int32_t x_i_ctrl = (int32_t)k_i * integral_x_err / I_CTRL_DIV;
    int32_t y_i_ctrl = (int32_t)k_i * integral_y_err / I_CTRL_DIV;
    int32_t x_d_ctrl = (int32_t)k_d * (x_err - last_x_err) * D_CTRL_MUL / (int32_t)timer_delta;
    int32_t y_d_ctrl = (int32_t)k_d * (y_err - last_y_err) * D_CTRL_MUL / (int32_t)timer_delta;

    *servo_y = -x_p_ctrl - x_i_ctrl - x_d_ctrl + SERVO_PULSE_MED;
    *servo_x = y_p_ctrl + y_i_ctrl + y_d_ctrl + SERVO_PULSE_MED;

    last_x_err = x_err;
    last_y_err = y_err;
    __HAL_TIM_GET_COUNTER(&htim21) = 0;
}