#ifndef __REDUCED_HAL_H
#define __REDUCED_HAL_H

#include "stm32l0xx_hal.h"

void tim_base_start(TIM_HandleTypeDef *htim);

void tim_pwm_start(TIM_HandleTypeDef *htim, uint32_t Channel);

#endif