#ifndef PIN_NAMES_H_
#define PIN_NAMES_H_

#include <inttypes.h>

/**
 * File containing all Pin Name macros and key grid size information.
 * 
 * @author DMark
 */

#define USR_LED_GPIO ((uint8_t) 25)
#define KEY_LED_GPIO ((uint8_t) 24)

#define ENCODER_CW_GPIO ((uint8_t) 17)
#define ENCODER_CCW_GPIO ((uint8_t) 18)

#define NUM_ROWS ((uint8_t) 6)
#define ROW0_GPIO ((uint8_t) 10)
#define ROW1_GPIO ((uint8_t) 11)
#define ROW2_GPIO ((uint8_t) 12)
#define ROW3_GPIO ((uint8_t) 13)
#define ROW4_GPIO ((uint8_t) 14)
#define ROW5_GPIO ((uint8_t) 15)

extern const uint8_t row_gpios[NUM_ROWS];

#define NUM_COLS ((uint8_t) 4)
#define COL0_GPIO ((uint8_t) 0)
#define COL1_GPIO ((uint8_t) 1)
#define COL2_GPIO ((uint8_t) 2)
#define COL3_GPIO ((uint8_t) 3)

extern const uint8_t col_gpios[NUM_COLS];

#endif