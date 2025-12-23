cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_FLAGS_RELEASE "-Og -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_SDK_PATH "C:/RaspberryPiPico/pico-sdk" CACHE PATH "Path to the Pico SDK")
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(picow_project C CXX ASM)

set(PICO_BOARD pico)
set(PICO_WIFI 0)
set(PICO_CYW43_SUPPORTED 0)
set(PICO_ENABLE_TINYUSB 1)

pico_sdk_init()

add_executable(usb_numpad_v1_0
    src/main.c
    src/usb_descriptors.c
    src/core0_tasks.c
    src/core1_tasks.c
    src/setup.c
    src/callbacks.c
    src/pin_names.c
    src/states.c
    src/numpad_config.c
    src/flash_functions.c
    src/custom_libs/gpio_custom.c
)

pico_generate_pio_header(usb_numpad_v1_0 ${CMAKE_CURRENT_SOURCE_DIR}/sk6812mini.pio)

target_include_directories(usb_numpad_v1_0 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(usb_numpad_v1_0 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/custom_libs)
target_include_directories(usb_numpad_v1_0 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/asm)

target_link_libraries(usb_numpad_v1_0
    pico_stdlib
    tinyusb_device
    tinyusb_board
    hardware_pwm
    pico_multicore
    hardware_pio
    hardware_dma
)

pico_add_extra_outputs(usb_numpad_v1_0)