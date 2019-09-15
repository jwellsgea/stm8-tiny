/*!
 * @file
 * @brief
 */

#include "stm8s.h"
#include "watchdog.h"

enum {
  unlock = 0x55,
  start = 0xCC,
  refresh = 0xAA
};

void watchdog_init(void) {
  // Unlock the IWDG registers and start watchdog
  IWDG->KR = unlock;
  IWDG->KR = start;

  // T = 2 * Tlsi * P * R
  // T = timeout
  // Tlsi = 1 / Flsi
  // Flsi = 128 KHz
  // P = 2 ^ (PR[2:0] + 2)
  // R = RLR[7:0] + 1
  //
  // PR[2:0] = 6, RLR[7:0] = 0xFF => ~1020 msec
  IWDG->PR = 0x3;
  IWDG->RLR = 0xFF;

  // Lock the IWDG registers and actually start counting
  IWDG->RLR = refresh;
}

void watchdog_kick(void) {
  IWDG->KR = refresh;
}
