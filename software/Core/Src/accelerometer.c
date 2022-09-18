#include <stdbool.h>
#include "stm32l0xx_hal.h"
#include "i2c.h"
#include "accelerometer.h"

#define ACCELEROMETER_I2C_ADDR 0x18
#define ACCELERATION_REG_ADDR 0x28 | (1 << 7) // OUT_X_L with auto-increment
#define CTRL_REG1_ADDR 0x20
#define CTRL_REG1_VALUE 0b01010111 // 100 Hz, normal power, all axis enabled
#define ACCELERATION_DATA_SIZE 6
#define ACCELERATION_RESOLUTION_BITS 10
#define READY_TRIALS 100

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
static volatile bool read_ready = false;

/**
 * @brief Wait for accelerometer to be ready for communications
 */
static void wait_accelerometer(void)
{
    while (HAL_I2C_IsDeviceReady(&hi2c1,
                                 ACCELEROMETER_I2C_ADDR << 1,
                                 READY_TRIALS,
                                 HAL_MAX_DELAY) == HAL_BUSY)
        ;
}

void accelerometer_init(void)
{
    uint8_t ctrl1_reg = CTRL_REG1_VALUE;
    wait_accelerometer();

    if (HAL_I2C_Mem_Write(&hi2c1,
                          ACCELEROMETER_I2C_ADDR << 1,
                          CTRL_REG1_ADDR,
                          I2C_MEMADD_SIZE_8BIT,
                          &ctrl1_reg,
                          1,
                          HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }
}

void begin_accelerometer_read(void)
{
    wait_accelerometer();
    if (HAL_I2C_Mem_Read_IT(&hi2c1,
                            ACCELEROMETER_I2C_ADDR << 1,
                            ACCELERATION_REG_ADDR,
                            I2C_MEMADD_SIZE_8BIT,
                            data_buf,
                            ACCELERATION_DATA_SIZE) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Converts acceleration data buffer to acceleration units
 * @param lsb_addr: Least significant byte address
 * @param msb_addr: Most significant byte address
 */
static inline int16_t buf_to_accel(uint8_t lsb_addr, uint8_t msb_addr)
{
    int16_t accel = (data_buf[msb_addr] << 8) | data_buf[lsb_addr];
    accel >>= 16 - ACCELERATION_RESOLUTION_BITS;
    return accel;
}

void get_acceleration(acceleration_t *accel)
{
    accel->x = buf_to_accel(OUT_X_L, OUT_X_H);
    accel->y = buf_to_accel(OUT_Y_L, OUT_Y_H);
    accel->z = buf_to_accel(OUT_Z_L, OUT_Z_H);
    read_ready = false;
}

void notify_accelerometer_read_ready(void)
{
    read_ready = true;
}

bool accelerometer_read_ready(void)
{
    return read_ready;
}