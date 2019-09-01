/*!
 * @file
 * @brief
 */

#include "accelerometer_plugin.h"
#include "data_model.h"
#include "tiny_utils.h"

enum {
  device_address = 0x1D,
  xyz_address = 0x28 + (1 << 7),
  update_period = 100 // fixme this should probably be much shorter
};

static void xyz_read(void* context, bool success) {
  reinterpret(self, context, accelerometer_plugin_t*);

  if(success) {
    self->update_ready = true;
  }
}

static void address_written(void* context, bool success) {
  reinterpret(self, context, accelerometer_plugin_t*);

  if(success) {
    tiny_i2c_read(
      self->i2c,
      device_address,
      false,
      &self->x,
      sizeof(int16_t) * 3,
      xyz_read,
      self);
  }
}

static void start_update(accelerometer_plugin_t* self) {
  const uint8_t address = xyz_address;

  tiny_i2c_write(
    self->i2c,
    device_address,
    true,
    &address,
    sizeof(address),
    address_written,
    self);
}

static void arm_update_timer(accelerometer_plugin_t* self, tiny_timer_group_t* timer_group);

typedef union {
  int16_t i16;
  struct {
    uint8_t low;
    uint8_t high;
  };
} swap_t;

static int16_t swap(int16_t i16) {
  swap_t s;
  s.i16 = i16;
  return (s.high << 8) + s.low;
}

static void update(tiny_timer_group_t* timer_group, void* context) {
  reinterpret(self, context, accelerometer_plugin_t*);

  if(self->update_ready) {
    self->x = swap(self->x);
    self->y = swap(self->y);
    self->z = swap(self->z);

    tiny_key_value_store_write(self->key_value_store, key_accelerometer_x, &self->x);
    tiny_key_value_store_write(self->key_value_store, key_accelerometer_y, &self->y);
    tiny_key_value_store_write(self->key_value_store, key_accelerometer_z, &self->z);

    self->update_ready = false;
  }
  else {
    tiny_i2c_reset(self->i2c);
  }

  start_update(self);

  arm_update_timer(self, timer_group);
}

static void arm_update_timer(accelerometer_plugin_t* self, tiny_timer_group_t* timer_group) {
  tiny_timer_start(timer_group, &self->timer, update_period, update, self);
}

void accelerometer_plugin_init(
  accelerometer_plugin_t* self,
  i_tiny_key_value_store_t* key_value_store,
  tiny_timer_group_t* timer_group) {
  self->key_value_store = key_value_store;
  self->update_ready = 0;
  self->i2c = i2c_init();

  arm_update_timer(self, timer_group);
}
