#include "potentiometers.h"
#include "adc.h"
#include "stm32l0xx_hal.h"

static uint8_t data_buf[NUM_POTENTIOMETERS];
static volatile bool read_ready = false;

void potentiometers_init(void)
{
    if (HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED) != HAL_OK)
    {
        Error_Handler();
    }
}

void begin_potentiometers_read(void)
{
    if (HAL_ADC_Start_DMA(&hadc, (uint32_t *)data_buf, NUM_POTENTIOMETERS) != HAL_OK)
    {
        Error_Handler();
    }
}

void notify_potentiometers_read_ready(void)
{
    read_ready = true;
}

bool potentiometers_read_ready(void)
{
    return read_ready;
}

uint8_t *get_potentiometers(void)
{
    read_ready = false;
    return data_buf;
}