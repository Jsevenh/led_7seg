cmake_minimum_required(VERSION 3.29.2)
set(BOARD rpi_pico)


find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(led_7seg)

target_sources(app PRIVATE src/main.c  src/z7seg.c)