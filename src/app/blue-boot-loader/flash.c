/*!
 * @file
 * @brief
 */

#include "flash.h"
#include "stm8s_flash.h"
#include "configuration.h"

#define enable_block_programming() \
  FLASH->PUKR = FLASH_RASS_KEY1;   \
  FLASH->PUKR = FLASH_RASS_KEY2;

#define wait_for_programming_to_complete()   \
  while(!(FLASH->IAPSR & FLASH_IAPSR_EOP)) { \
  }

static volatile uint8_t flash_code_size;
static uint8_t ram_write_block[128];

static void unlock_flash(void) {
  FLASH->PUKR = FLASH_RASS_KEY1;
  FLASH->PUKR = FLASH_RASS_KEY2;

  while(!(FLASH->IAPSR & FLASH_IAPSR_PUL)) {
  }
}

#pragma codeseg flash_code_segment
static void write_block(volatile uint8_t* address, const uint8_t* data) {
  enable_block_programming();

  for(uint8_t i = 0; i < block_size; i++) {
    address[i] = data[i];
  }

  wait_for_programming_to_complete();
}

inline void get_flash_code_size(void) {
  __asm__("mov _flash_code_size, #l_flash_code_segment");
}

inline void copy_flash_code_to_ram(void) {
  for(uint8_t i = 0; i < flash_code_size; i++) {
    ram_write_block[i] = ((const uint8_t*)write_block)[i];
  }
}

void flash_init(void) {
  get_flash_code_size();
  copy_flash_code_to_ram();
  unlock_flash();
}

void flash_write_block(volatile uint8_t* address, const uint8_t* data) {
  ((void (*)(volatile uint8_t*, const uint8_t*))ram_write_block)(address, data);
}

void flash_write_byte(volatile uint8_t* address, uint8_t byte) {
  *address = byte;
  wait_for_programming_to_complete();
}
