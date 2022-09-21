#include "potentiometers.h"
#include "adc.h"
#include "stm32l0xx_hal.h"

static uint16_t data_buf[NUM_POTENTIOMETERS];
static uint8_t result[NUM_POTENTIOMETERS];
static volatile bool read_ready = false;

void potentiometers_init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);
}

void begin_potentiometers_read(void)
{
    HAL_ADC_Start_DMA(&hadc, (uint32_t *)data_buf, NUM_POTENTIOMETERS);
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

    result[0] = data_buf[0] >> 4;
    result[1] = data_buf[1] >> 4;
    result[2] = data_buf[2] >> 4;
    return result;
}