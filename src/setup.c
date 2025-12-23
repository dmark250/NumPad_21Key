#include "pico/stdlib.h"

#include "pin_names.h"
#include "setup.h"
#include "numpad_config.h"
#include "hardware/pio.h"
#include "sk6812mini.pio.h"

/**
 * Contains all setup functions, made to be called in main setup.
 * 
 * @author DMark
 */

void usr_led_setup(void) {
    gpio_init(USR_LED_GPIO);
    gpio_set_dir(USR_LED_GPIO, GPIO_OUT);
    gpio_put(USR_LED_GPIO, 0);
}

/**
 * Sets up the grid gpio pins for reading keys
 */
void grid_setup(void) {
    int i;
    for (i = 0; i < NUM_ROWS; i++) {
        gpio_init(row_gpios[i]);
        gpio_set_dir(row_gpios[i], GPIO_IN);
        gpio_set_pulls(row_gpios[i], false, true);
    }
    for (i = 0; i < NUM_COLS; i++) {
        gpio_init(col_gpios[i]);
        gpio_set_dir(col_gpios[i], GPIO_OUT);
        gpio_put(col_gpios[i], 0);
    }
}

void encoder_setup(void) {
    gpio_init(ENCODER_CCW_GPIO);
    gpio_init(ENCODER_CW_GPIO);
    gpio_set_dir(ENCODER_CCW_GPIO, GPIO_IN);
    gpio_set_dir(ENCODER_CW_GPIO, GPIO_IN);
    gpio_disable_pulls(ENCODER_CCW_GPIO);
    gpio_disable_pulls(ENCODER_CW_GPIO);
}
