/*!
 * @file
 * @brief
 */

#include <stdbool.h>
#include <stddef.h>
#include "stm8s.h"
#include "clock.h"
#include "watchdog.h"
#include "flash.h"
#include "boot_loader.h"

enum {
  boot_loader = 0xB1,
  app = ~boot_loader
};

// fixme this needs to be in a specific spot
// fixme eeprom
static const uint8_t mode;

void main(void) {
  if((mode != boot_loader) && boot_loader_app_is_valid()) {
    boot_loader_jump_to_app();
  }

  watchdog_init();
  clock_init();
  flash_init();

  // fixme eeprom
  flash_write_byte((volatile uint8_t*)mode, app);

  boot_loader_receive_app();

  while(true) {
  }
}
