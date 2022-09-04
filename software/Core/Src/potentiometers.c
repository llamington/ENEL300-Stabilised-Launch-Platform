#include "potentiometers.h"
#include "adc.h"
#include "stm32l0xx_hal.h"

#define NUM_POTENTIOMETERS 3

static uint32_t data_buf[NUM_POTENTIOMETERS];

void begin_potentiometers_read(void)
{
    HAL_ADC_Start_DMA(&hadc, data_buf, NUM_POTENTIOMETERS);
}

uint32_t *get_potentiometers(void)
{
    return data_buf;
}