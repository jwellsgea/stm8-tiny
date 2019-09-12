/*!
 * @file
 * @brief
 */

#ifndef boot_loader_h
#define boot_loader_h

#include <stdbool.h>
#include "configuration.h"
#include "utils.h"

#define boot_loader_jump_to_app() \
  __asm__("jp " STR(app_address))

bool boot_loader_app_is_valid(void);

void boot_loader_receive_app(void);

#endif
