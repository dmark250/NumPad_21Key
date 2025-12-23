#ifndef NUMPAD_CONFIG_H_
#define NUMPAD_CONFIG_H_

#include <inttypes.h>
#include "pin_names.h"

/**
 * Contains numpad_config_t variable declarations and structs.
 * 
 * @author DMark
 */

#define NUM_USR_CONFIGS 3

typedef struct {
    uint8_t key_codes[NUM_ROWS][NUM_COLS];
    uint8_t rgb_values[21][3];
} numpad_config_t;

extern numpad_config_t default_config;
extern numpad_config_t user_configs[3];
extern numpad_config_t *current_config;


#endif