#ifndef SETUP_H_
#define SETUP_H_

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "sk6812mini.pio.h"
#include "hardware/clocks.h"

/**
 * Setup header file.
 * 
 * @author DMark
 */

void usr_led_setup(void);
void grid_setup(void);
void encoder_setup(void);

/**
 * Initializes PIO for programming a series of inline sk6812mini LEDs
 * via bit banging.
 */
static inline void sk6812mini_program_init(PIO pio, uint sm, uint offset, float frequency) {
    pio_gpio_init(pio, KEY_LED_GPIO);
    pio_sm_set_consecutive_pindirs(pio, sm, KEY_LED_GPIO, 1, true);
    pio_sm_config config = sk6812mini_program_get_default_config(offset);
    sm_config_set_sideset_pins(&config, KEY_LED_GPIO);
    sm_config_set_out_shift(&config, false, true, 24);
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);

    int cycles_per_bit = sk6812mini_T1 + sk6812mini_T2 + sk6812mini_T3;
    float div = clock_get_hz(clk_sys) / (frequency * cycles_per_bit);
    sm_config_set_clkdiv(&config, div);

    pio_sm_init(pio, sm, offset, &config);
    pio_sm_set_enabled(pio, sm, true);
}

#endif