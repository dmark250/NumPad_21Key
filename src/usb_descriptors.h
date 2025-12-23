#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

#include <stdint.h>
#include "tusb.h"

/**
 * Defines external descriptor variables and callbacks used
 * by tinyusb.
 */

extern const uint8_t hid_report_descriptor[];
extern const uint16_t hid_report_descriptor_size;

extern const tusb_desc_device_t device_descriptor;

uint8_t const * tud_descriptor_device_cb(void);
uint8_t const * tud_descriptor_configuration_cb(uint8_t index);
uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance);
uint16_t const * tud_descriptor_string_cb(uint8_t index, uint16_t langid);

#define POLLING_RATE_MS 5

enum {
  REPORT_ID_KEYBOARD = 1,
  REPORT_ID_MOUSE,
  REPORT_ID_CONSUMER_CONTROL,
  REPORT_ID_GAMEPAD,
  REPORT_ID_COUNT
};

#endif