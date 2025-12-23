#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <inttypes.h>
#include "pico/stdlib.h"

int64_t set_toggle_usr_led_cb(alarm_id_t id, void* user_data);
bool set_read_grid_cb(repeating_timer_t *timer);
bool set_update_key_led_cb(repeating_timer_t *timer);

#endif