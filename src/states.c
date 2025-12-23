#include "states.h"
#include "blink_rate.h"
#include "pin_names.h"

/**
 * Contains the global state machine states and 
 * grid states variables.
 * 
 * @author DMark
 */

volatile state_machine states = {
    .read_grid = 0, 
    .toggle_usr_led = 0,
    .mounted_state = UMOUNTED_STATE,
    .encoder_cw_state = 0,
    .encoder_ccw_state = 0,
    .rotate_cw = 0,
    .rotate_ccw = 0,
    .update_key_led = 0,
    .encoder_pressed = 0,
    .encoder_press_confirmed = 0,
    .config_number = 0,
    .key_led_brightness = 3
};

volatile uint8_t grid_states[NUM_ROWS][NUM_COLS] = {0};
