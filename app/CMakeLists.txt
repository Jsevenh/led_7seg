cmake_minimum_required(VERSION 3.29.2)

include_directories(/home/mbayi/pico/pico-sdk/src/rp2_common/hardware_pio/include/hardware)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

add_subdirectory(pio)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
project(led_7seg)

target_sources(app PRIVATE src/main.c  src/z7seg.c )