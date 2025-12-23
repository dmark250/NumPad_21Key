#ifndef STATES_H_
#define STATES_H_

#include <inttypes.h>
#include "pin_names.h"

/**
 * Defines the brightness multiplier, state_machine struct, and 
 * global states variables.
 * 
 * @author DMark
 */

#define BRIGHTNESS_MULTIPLIER ((unsigned int) (1 << 2) * (1 << 2))

typedef struct state_machine {
    unsigned int read_grid : 1;
    unsigned int toggle_usr_led : 1;
    unsigned int mounted_state : 2;
    unsigned int encoder_cw_state : 1;
    unsigned int encoder_ccw_state : 1;
    unsigned int rotate_cw : 1;
    unsigned int rotate_ccw : 1;
    unsigned int update_key_led : 1;
    unsigned int key_led_brightness : 2;
    unsigned int encoder_pressed : 1;
    unsigned int encoder_press_confirmed : 1;
    unsigned int config_number : 2;
} state_machine;

extern volatile state_machine states;
extern volatile uint8_t grid_states[NUM_ROWS][NUM_COLS];

#endif