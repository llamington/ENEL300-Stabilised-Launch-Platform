#ifndef __POTENTIOMETERS_H
#define __POTENTIOMETERS_H

#include <stdint.h>

/**
 * @brief Begin the reading of potentiometer values
 */
void begin_potentiometers_read(void);

/**
 * @brief Get the potentiometer values
 */
uint32_t *get_potentiometers(void);

#endif