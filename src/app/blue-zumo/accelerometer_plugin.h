/*!
 * @file
 * @brief
 */

#ifndef accelerometer_plugin_th
#define accelerometer_plugin_th

#include "i_tiny_key_value_store.h"
#include "i2c.h"
#include "tiny_timer.h"

typedef struct {
  tiny_timer_t timer;
  i_tiny_key_value_store_t* key_value_store;
  i_tiny_i2c_t* i2c;

  int16_t x;
  int16_t y;
  int16_t z;
  bool update_ready;
} accelerometer_plugin_t;

void accelerometer_plugin_init(
  accelerometer_plugin_t* self,
  i_tiny_key_value_store_t* key_value_store,
  tiny_timer_group_t* timer_group);

#endif
