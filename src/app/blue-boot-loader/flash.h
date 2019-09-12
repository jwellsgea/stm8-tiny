/*!
 * @file
 * @brief
 */

#ifndef flash_h
#define flash_h

#include <stdint.h>

void flash_init(void);

void flash_write_block(volatile uint8_t* address, const uint8_t* data);

void flash_write_byte(volatile uint8_t* address, uint8_t byte);

#endif
