#include "potentiometers.h"
#include "adc.h"
#include "stm32l0xx_hal.h"

void begin_potentiometers_read(void)
{
    HAL_ADC_Start_IT(&hadc);
}