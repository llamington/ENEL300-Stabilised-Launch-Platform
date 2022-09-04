#include "potentiometers.h"
#include "adc.h"
#include "stm32l0xx_hal.h"

#define NUM_POTENTIOMETERS 3

static uint32_t data_buf[NUM_POTENTIOMETERS];
static volatile bool read_ready = false;

void begin_potentiometers_read(void)
{
    HAL_ADC_Start_DMA(&hadc, data_buf, NUM_POTENTIOMETERS);
}

void notify_potentiometers_read_ready(void)
{
    read_ready = true;
}

bool potentiometers_read_ready(void)
{
    return read_ready;
}

uint32_t *get_potentiometers(void)
{
    read_ready = false;
    return data_buf;
}