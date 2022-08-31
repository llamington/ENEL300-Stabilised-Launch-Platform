#include "stm32l0xx_hal.h"
#include "i2c.h"
#include "accelerometer.h"

#define ACCELEROMETER_I2C_ADDR 0x18
#define ACCELERATION_REG_ADDR 0x28 & (1 << 7) // OUT_X_L with auto-increment
#define ACCELERATION_DATA_SIZE 6
#define ACCELERATION_RESOLUTION_BITS 10

/**
 * @brief Acceleration output indices
 */
enum
{
    OUT_X_L,
    OUT_X_H,
    OUT_Y_L,
    OUT_Y_H,
    OUT_Z_L,
    OUT_Z_H
};

static uint8_t data_buf[ACCELERATION_DATA_SIZE];

void begin_accelerometer_read(void)
{
    HAL_I2C_Mem_Read_IT(&hi2c1,
                        ACCELEROMETER_I2C_ADDR << 1,
                        ACCELERATION_REG_ADDR,
                        I2C_MEMADD_SIZE_8BIT,
                        data_buf,
                        ACCELERATION_DATA_SIZE);
}

void get_acceleration(acceleration_t *accel)
{
    accel->x = (data_buf[OUT_X_H] << 8) & data_buf[OUT_X_L];
    accel->x >>= 16 - ACCELERATION_RESOLUTION_BITS;
    accel->y = (data_buf[OUT_Y_H] << 8) & data_buf[OUT_Y_L];
    accel->y >>= 16 - ACCELERATION_RESOLUTION_BITS;
    accel->z = (data_buf[OUT_Z_H] << 8) & data_buf[OUT_Z_L];
    accel->z >>= 16 - ACCELERATION_RESOLUTION_BITS;
}