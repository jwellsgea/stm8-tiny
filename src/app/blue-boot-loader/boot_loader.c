/*!
 * @file
 * @brief
 */

#include <stdbool.h>
#include "boot_loader.h"
#include "uart1.h"
#include "watchdog.h"
#include "protocol.h"
#include "configuration.h"
#include "tiny_crc16.h"
#include "flash.h"

#define vector_table_address 0x8004
#define vector_size 4
#define vector_table_size 128

bool boot_loader_app_is_valid(void) {
  // app_crc_address
  // fixme

  return true;
}

typedef struct {
  uint8_t block;
  uint8_t data[block_size];
  uint16_t crc;
} receive_buffer_t;

static uint8_t current_block = 0;
static uint8_t calculated_crc;
static receive_buffer_t receive_buffer;

void boot_loader_receive_app(void) {
  while(true) {
    watchdog_kick();

    if(uart1_read() != start_frame) {
      continue;
    }

    calculated_crc = 0;

    for(uint8_t i = 0; i < sizeof(receive_buffer); i++) {
      ((uint8_t*)&receive_buffer)[i] = (uart1_read() << 4) | uart1_read();
      calculated_crc = tiny_crc16_calculate(calculated_crc, ((uint8_t*)&receive_buffer)[i]);
    }

    if((current_block <= receive_buffer.block) && (calculated_crc == receive_buffer.crc)) {
      if(current_block == receive_buffer.block) {
        flash_write_block(
          (volatile uint8_t*)(app_address + current_block * block_size),
          receive_buffer.data);

        current_block++;
      }

      uart1_write(ack);
    }
    else {
      uart1_write(nack);
    }

    if(current_block == app_size_in_blocks) {
      break;
    }
  }

  // Skip the reset vector so that we don't break the boot loader
  for(uint8_t i = vector_size; i < vector_table_size; i++) {
    flash_write_byte(
      (volatile uint8_t*)(vector_table_address + i),
      *(volatile uint8_t*)(app_vector_table_address + i));
  }
}
