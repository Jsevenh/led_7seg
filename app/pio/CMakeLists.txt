cmake_minimum_required(VERSION 3.29.2)

pico_generate_pio_header(hello_pio ${CMAKE_CURRENT_LIST_DIR}/hello.pio)

# add url via pico_set_program_url
