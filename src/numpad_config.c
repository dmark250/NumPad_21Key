#include "numpad_config.h"
#include "pin_names.h"
#include "tusb.h"

/**
 * Holds numpad configuration data, including HID values and LED colors.
 * 
 * @author DMark
 */



numpad_config_t default_config = {.key_codes = {
        {HID_KEY_COPY, HID_KEY_NUM_LOCK, HID_KEY_TAB, HID_KEY_NONE},
        {HID_KEY_BACKSPACE, HID_KEY_KEYPAD_DIVIDE, HID_KEY_KEYPAD_MULTIPLY, HID_KEY_KEYPAD_SUBTRACT},
        {HID_KEY_KEYPAD_7, HID_KEY_KEYPAD_8, HID_KEY_KEYPAD_9, HID_KEY_KEYPAD_ADD},
        {HID_KEY_KEYPAD_4, HID_KEY_KEYPAD_5, HID_KEY_KEYPAD_6, HID_KEY_EQUAL},
        {HID_KEY_KEYPAD_1, HID_KEY_KEYPAD_2, HID_KEY_KEYPAD_3, HID_KEY_KEYPAD_ENTER},
        {HID_KEY_KEYPAD_0, HID_KEY_NONE, HID_KEY_KEYPAD_DECIMAL, HID_KEY_NONE}  
        }, .rgb_values = {
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF},
        {0x00, 0x00, 0xFF},
        {0x00, 0x00, 0xFF},
        {0x00, 0x00, 0xFF},
        {0x00, 0x00, 0xFF},
        {0x00, 0x00, 0xFF},
        {0x00, 0x00, 0xFF}
        }
};

numpad_config_t user_configs[3] = {
    {
        .key_codes = {
        {HID_KEY_COPY, HID_KEY_NUM_LOCK, HID_KEY_TAB, HID_KEY_NONE},
        {HID_KEY_BACKSPACE, HID_KEY_KEYPAD_DIVIDE, HID_KEY_KEYPAD_MULTIPLY, HID_KEY_KEYPAD_SUBTRACT},
        {HID_KEY_KEYPAD_7, HID_KEY_KEYPAD_8, HID_KEY_KEYPAD_9, HID_KEY_KEYPAD_ADD},
        {HID_KEY_KEYPAD_4, HID_KEY_KEYPAD_5, HID_KEY_KEYPAD_6, HID_KEY_EQUAL},
        {HID_KEY_KEYPAD_1, HID_KEY_KEYPAD_2, HID_KEY_KEYPAD_3, HID_KEY_KEYPAD_ENTER},
        {HID_KEY_KEYPAD_0, HID_KEY_NONE, HID_KEY_KEYPAD_DECIMAL, HID_KEY_NONE}  
        }, .rgb_values = {
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00},
        {0xFF, 0x00, 0x00}
        }
    },
    {
        .key_codes = {
        {HID_KEY_COPY, HID_KEY_NUM_LOCK, HID_KEY_TAB, HID_KEY_NONE},
        {HID_KEY_BACKSPACE, HID_KEY_KEYPAD_DIVIDE, HID_KEY_KEYPAD_MULTIPLY, HID_KEY_KEYPAD_SUBTRACT},
        {HID_KEY_KEYPAD_7, HID_KEY_KEYPAD_8, HID_KEY_KEYPAD_9, HID_KEY_KEYPAD_ADD},
        {HID_KEY_KEYPAD_4, HID_KEY_KEYPAD_5, HID_KEY_KEYPAD_6, HID_KEY_EQUAL},
        {HID_KEY_KEYPAD_1, HID_KEY_KEYPAD_2, HID_KEY_KEYPAD_3, HID_KEY_KEYPAD_ENTER},
        {HID_KEY_KEYPAD_0, HID_KEY_NONE, HID_KEY_KEYPAD_DECIMAL, HID_KEY_NONE}  
        }, .rgb_values = {
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00},
        {0x00, 0xFF, 0x00}
        }
    },
    {
        .key_codes = {
        {HID_KEY_COPY, HID_KEY_NUM_LOCK, HID_KEY_TAB, HID_KEY_NONE},
        {HID_KEY_BACKSPACE, HID_KEY_KEYPAD_DIVIDE, HID_KEY_KEYPAD_MULTIPLY, HID_KEY_KEYPAD_SUBTRACT},
        {HID_KEY_KEYPAD_7, HID_KEY_KEYPAD_8, HID_KEY_KEYPAD_9, HID_KEY_KEYPAD_ADD},
        {HID_KEY_KEYPAD_4, HID_KEY_KEYPAD_5, HID_KEY_KEYPAD_6, HID_KEY_EQUAL},
        {HID_KEY_KEYPAD_1, HID_KEY_KEYPAD_2, HID_KEY_KEYPAD_3, HID_KEY_KEYPAD_ENTER},
        {HID_KEY_KEYPAD_0, HID_KEY_NONE, HID_KEY_KEYPAD_DECIMAL, HID_KEY_NONE}  
        }, .rgb_values = {
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF},
        {0x00, 0x80, 0xFF}
        }
    }
};

numpad_config_t *current_config = &default_config;