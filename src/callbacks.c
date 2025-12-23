#include "pico/stdlib.h"
#include "callbacks.h"
#include "states.h"
#include "blink_rate.h"

/**
 * sets toggle_usr_led state at a recurring rate based on mounted state.
 */
int64_t set_toggle_usr_led_cb(alarm_id_t id, void* user_data) {
    states.toggle_usr_led = 1;
    switch (states.mounted_state) {
        case MOUNTED_STATE :
            return BLINK_MOUNTED;
            break;
        case UMOUNTED_STATE :
            return BLINK_UMOUNTED;
            break;
        case SUSPENDED_STATE :
            return BLINK_SUSPENDED;
            break;
        default :
            return 0;
    }
}

/**
 * recurring read grid state set callback.
 */
bool set_read_grid_cb(repeating_timer_t *timer) {
    states.read_grid = 1;
    return true;
}

/**
 * recurring update key led state set callback.
 */
bool set_update_key_led_cb(repeating_timer_t *timer) {
    states.update_key_led = 1;
    return true;
}