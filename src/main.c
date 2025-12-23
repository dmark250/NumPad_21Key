#include "pico/stdlib.h"
#include "tusb.h"
#include "bsp/board_api.h"
#include "pico/multicore.h"
#include "hardware/pio.h"
#include "sk6812mini.pio.h"
#include "hardware/dma.h"
#include "hardware/pio_instructions.h"

#include <stdbool.h>
#include <inttypes.h>

#include "usb_descriptors.h"
#include "tusb_config.h"
#include "pin_names.h"
#include "core0_tasks.h"
#include "core1_tasks.h"
#include "callbacks.h"
#include "setup.h"
#include "states.h"
#include "blink_rate.h"
#include "numpad_config.h"

/**
 * Main File for the program.
 * 
 * @author DMark
 */

void core1_main_function(void);
void gpio_irq_handler(uint gpio, uint32_t events);

int64_t set_hid_buffer_cb(alarm_id_t id, void *user_data);

PIO pio = pio0;
uint sm;
uint offset;

/**
 * Core 0 main function
 */
int main(void) {

    // startup pio for led addressing, initializing all as off.
    sm = pio_claim_unused_sm(pio, false);
    offset = pio_add_program(pio, &sk6812mini_program);
    sk6812mini_program_init(pio0, sm, offset, 800000);
    for (int i = 0; i < 21; i++) {
        pio_sm_put_blocking(pio0, 0, (uint32_t)0);
    }

    // setup pins for usr led, key grid, and encoder.
    usr_led_setup();
    grid_setup();
    encoder_setup();
    irq_set_enabled(IO_IRQ_BANK0, true);
    gpio_set_irq_callback(gpio_irq_handler);
    gpio_set_irq_enabled(ENCODER_CW_GPIO, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(ENCODER_CCW_GPIO, GPIO_IRQ_EDGE_RISE| GPIO_IRQ_EDGE_FALL, true);

    // setup timers for updating state machines.
    repeating_timer_t read_grid_states_timer;
    add_repeating_timer_ms(1, set_read_grid_cb, NULL, &read_grid_states_timer);
    repeating_timer_t update_key_led_timer;
    add_repeating_timer_ms(200, set_update_key_led_cb, NULL, &update_key_led_timer);

    // Initialize core1 and usb communication.
    multicore_launch_core1(core1_main_function);
    tusb_init();
    tud_init(BOARD_TUD_RHPORT);
    states.update_key_led = 1;

    // Main loop for Core0, NOTE: keep minimal for consistent usb communication.
    while (1) {
        tud_task();
        tight_loop_contents();
        switch (states.toggle_usr_led) {
        case 1:
            static bool led_on = false;
            led_on = !led_on;
            gpio_put(USR_LED_GPIO, led_on);
            states.toggle_usr_led = 0;
            break;
        
        default:
            break;
        }
    }

    return 0;
}

/**
 * Core 1 Main function.
 */
void core1_main_function(void) {
    while (1) {
        // Reads key grid states, setting grid_states accordingly
        // NOTE: CAN BE OPTIMIZED, CURRENTLY HAS SLEEP_US() TO FIX
        //       BUTTON PRESSING INCONSISTENCY ISSUE. UNSURE IF PROBLEM
        //       IS CAUSED BY COMPILER OPTIMIZATIONS. MAY NEED TO REMOVE
        //       100 nF CAPS ON ROW INPUTS.
        if (states.read_grid) {
            static int read_grid_row;
            read_grid_row = 0;
            static int read_grid_col;
            read_grid_col = 0;
            for (read_grid_col = 0; read_grid_col < NUM_COLS; read_grid_col++) {
                gpio_put(col_gpios[read_grid_col], 1);
                for (read_grid_row = 0; read_grid_row < NUM_ROWS; read_grid_row++) {
                    if (read_grid_col == 3 && read_grid_row == 0) {
                        states.encoder_pressed = gpio_get(ROW0_GPIO);
                        if (!states.encoder_pressed) {
                            states.encoder_press_confirmed = 0;
                        }
                    }
                    else if (gpio_get(row_gpios[read_grid_row])) {
                        grid_states[read_grid_row][read_grid_col] = 1;
                    }
                }
                gpio_put(col_gpios[read_grid_col], 0);
                sleep_us(1);
            }

            states.read_grid = 0;
        }
        // does operation once on encoder press.
        if (states.encoder_pressed & !states.encoder_press_confirmed) {
            states.encoder_press_confirmed |= 1;
            states.update_key_led |= 1;
            switch (states.config_number) {
            case 0:
                states.config_number++;
                current_config = &user_configs[0];
                break;
            case 1:
                states.config_number++;
                current_config = &user_configs[1];
                break;
            case 2:
                states.config_number++;
                current_config = &user_configs[2];
                break;
            case 3:
                states.config_number &= 0;
                current_config = &default_config;
                break;
            default:
                break;
            }
        }
        // does operation once on encoder rotation.
        if (states.rotate_cw) {
            states.update_key_led |= 1;
            states.rotate_cw = 0;
            states.key_led_brightness++;
        } 
        if (states.rotate_ccw) {
            states.update_key_led |= 1;
            states.rotate_ccw = 0;
            states.key_led_brightness--;
        }
        // updates key LEDs.
        // NOTE: UPDATE USING DMA OR USING A CALLBACK TO REDUCE WASTED CYCLES.
        if (states.update_key_led) {
            states.update_key_led &= 0;
            for (int i = 0; i < 21; i++) {
                pio_sm_put_blocking(pio, sm, (uint32_t)((current_config->rgb_values[i][1] / BRIGHTNESS_MULTIPLIER * (1 << states.key_led_brightness - 1)) << 24) | ((current_config->rgb_values[i][0] / BRIGHTNESS_MULTIPLIER * (1 << states.key_led_brightness - 1)) << 16) | ((current_config->rgb_values[i][2] / BRIGHTNESS_MULTIPLIER * ( 1 << states.key_led_brightness - 1)) << 8));
            }
        }
    }
}

/**
 * Called when mounted via USB.
 * updates states to mounted.
 */
void tud_mount_cb(void) {
    // sends NULL report.
    if (tud_hid_ready()) {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    }
    states.mounted_state = MOUNTED_STATE;
}

/**
 * Called when unmounted via USB.
 * updates states to umounted.
 */
void tud_umount_cb(void) {
    states.mounted_state = UMOUNTED_STATE;
}

/**
 * Called when suspended via USB.
 * updates states to suspended.
 */
void tud_suspend_cb(bool remote_wakeup_en) {
    states.mounted_state = SUSPENDED_STATE;
}

/**
 * Called when unsuspended via USB.
 * updates states to resumed mounted state.
 */
void tud_resume_cb(void) {
    if (tud_hid_ready()) {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    }
    states.mounted_state = tud_mounted() ? MOUNTED_STATE : UMOUNTED_STATE;
}

/**
 * Called when report was sent via usb.
 * sets hid_buffer_cb to be called in 4 ms, 1 ms before next report request.
 */
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len) {
    add_alarm_in_ms(4, set_hid_buffer_cb, NULL, true);
}

/**
 * Called to setup a HID report using corresponding grid_states values.
 * TODO: ADD SOMETHING LIKE WATCHDOG TO ENSURE THIS IS CALLED
 *       IF IT HASN'T FOR >20 MS.
 */
int64_t set_hid_buffer_cb(alarm_id_t id, void *user_data) {
    static int hid_buffer_column = 0;
    static int hid_buffer_row = 0;
    static uint8_t buffer_keys[6] = {0};
    static uint8_t buffer_num = 0;
    buffer_num = 0;
    // zeros key buffer.
    while (buffer_num < 6) {
        buffer_keys[buffer_num] = 0;
        buffer_num++;
    }
    buffer_num = 0;
    // sets key buffer with actively pressed keys.
    for (hid_buffer_row = 0; hid_buffer_row < NUM_ROWS; hid_buffer_row++) {
        for (hid_buffer_column = 0; hid_buffer_column < NUM_COLS; hid_buffer_column++) {
            if (buffer_num > 5) {
                break;
            }
            if (grid_states[hid_buffer_row][hid_buffer_column]) {
                buffer_keys[buffer_num] = current_config->key_codes[hid_buffer_row][hid_buffer_column];
                buffer_num++;
            }
        }
    }
    if (!tud_hid_ready()) {
        return 500;
    }
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, buffer_keys);
    for (hid_buffer_column = 0; hid_buffer_column < NUM_COLS; hid_buffer_column++) {
        for (hid_buffer_row = 0; hid_buffer_row < NUM_ROWS; hid_buffer_row++) {
            grid_states[hid_buffer_row][hid_buffer_column] = 0;
        }
    }
    return 0;
}

// Called when host requests to get a report
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)reqlen;

    // Return length of copied report, or zero if none
    // For now, just send dummy data
    buffer[0] = 0;
    return 1;
}

/**
 * Called when host has sent an hid report to device.
 * updates usr led with num_lock state.
 */
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {

    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)bufsize;

    if (report_type == HID_REPORT_TYPE_OUTPUT && bufsize >= 1) {
        // sets num_lock LED state to match num_lock state.
        static bool num_lock_enabled;
        if (buffer[0] & KEYBOARD_LED_NUMLOCK) {
            if (!num_lock_enabled) {
                num_lock_enabled = true;
                gpio_put(USR_LED_GPIO, 1);
            }
        } else {
            if (num_lock_enabled) {
                num_lock_enabled = false;
                gpio_put(USR_LED_GPIO, 0);
            }
        }
    }
}

/**
 * GPIO interrupt handler function
 */
void gpio_irq_handler(uint gpio, uint32_t events) {
    switch (gpio) {
        // updates encoder states.
        // TODO: ADD DEBOUNCE (works without, 100 nF caps)
        case ENCODER_CW_GPIO :
            switch (events) {
            case GPIO_IRQ_EDGE_FALL :
                if (!(states.encoder_cw_state | states.encoder_ccw_state)) {
                    states.rotate_cw = 1;
                }
                states.encoder_cw_state = 1;
                break;
            case GPIO_IRQ_EDGE_RISE :
                states.encoder_cw_state = 0;
                break;
            default :
                break;
            }
            break;
        
        case ENCODER_CCW_GPIO :
            switch (events) {
            case GPIO_IRQ_EDGE_FALL :
                if (!(states.encoder_cw_state | states.encoder_ccw_state)) {
                    states.rotate_ccw = 1;
                }
                states.encoder_ccw_state = 1;
                break;
            case GPIO_IRQ_EDGE_RISE :
                states.encoder_ccw_state = 0;
                break;
            default :
                break;
            }
            break;
        default:
            break;
    }

}