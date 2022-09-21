#include <stdbool.h>
#include "stm32l0xx_hal.h"
#include "i2c.h"
#include "accelerometer.h"

#define ACCELEROMETER_I2C_ADDR 0x18
#define ACCELERATION_REG_ADDR 0x28 | (1 << 7) // OUT_X_L with auto-increment
#define CTRL_REG1_ADDR 0x20
#define CTRL_REG1_VALUE 0b01011111 // 100 Hz, low-power, all axis enabled
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

/**
 * @brief Converts acceleration data buffer to acceleration units
 * @param lsb_addr: Least significant byte address
 * @param msb_addr: Most significant byte address
 */
static inline int16_t buf_to_accel(uint8_t lsb_addr, uint8_t msb_addr, uint8_t *data_buf)
{
    int16_t accel = (data_buf[msb_addr] << 8) | data_buf[lsb_addr];
    accel >>= 16 - ACCELERATION_RESOLUTION_BITS;
    return accel;
}

void read_acceleration(acceleration_t *accel)
{
    uint8_t buf[6];
    buf[0] = ACCELERATION_REG_ADDR;
    HAL_I2C_Master_Transmit(&hi2c1, ACCELEROMETER_I2C_ADDR << 1, buf, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, ACCELEROMETER_I2C_ADDR << 1, buf, ACCELERATION_DATA_SIZE, HAL_MAX_DELAY);
    accel->x = buf[OUT_X_H];
    accel->y = buf[OUT_Y_H];
    accel->z = buf[OUT_Z_H];
}

void accelerometer_init(void)
{
    uint8_t buf[] = {CTRL_REG1_ADDR, CTRL_REG1_VALUE};
    HAL_I2C_Master_Transmit(&hi2c1, ACCELEROMETER_I2C_ADDR << 1, buf, 2, HAL_MAX_DELAY);
}