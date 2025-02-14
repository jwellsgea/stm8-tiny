/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <stdlib.h>
#include "application.h"
#include "tiny_utils.h"

void application_init(application_t* self, tiny_timer_group_t* timer_group) {
  data_model_init(&self->data_model);
  i_tiny_key_value_store_t* store = data_model_key_value_store(&self->data_model);

  motors_plugin_init(&self->motors_plugin, store);
  line_sensors_plugin_init(&self->line_sensors_plugin, store, timer_group);
  accelerometer_plugin_init(&self->accelerometer_plugin, store, timer_group);
  strategy_plugin_init(&self->strategy_plugin, store, timer_group);
}
