#ifndef __POTENTIOMETERS_H
#define __POTENTIOMETERS_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_POTENTIOMETERS 3

/**
 * @brief Begin the reading of potentiometer values
 */
void begin_potentiometers_read(void);

/**
 * @brief Get the potentiometer values
 */
uint32_t *get_potentiometers(void);

/**
 * @brief Returns whether the potentiometer data is ready to be read
 */
bool potentiometers_read_ready(void);

/**
 * @brief Allow potentiometer data to be read
 */
void notify_potentiometers_read_ready(void);

#endif