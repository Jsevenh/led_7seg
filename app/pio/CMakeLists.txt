cmake_minimum_required(VERSION 3.29.2)
project(pio)
set(PICO_SDK_PATH "/home/mbayi/pico/pico-sdk")
 
# Initialize the Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
 set(PIO_FILE "${CMAKE_CURRENT_SOURCE_DIR}/7seg.pio" )
 set(C_FILE "${CMAKE_CURRENT_SOURCE_DIR}/csdk.c")
add_custom_command(
    OUTPUT ${PIO_FILE}
    COMMAND  python3 ${CMAKE_CURRENT_SOURCE_DIR}/pioasm.py ${PIO_FILE} ${C_FILE}
    DEPENDS ${C_FILE} 
    COMMENT "adding c-sdk to .pio...."
    VERBATIM
)
#target_sources(seg_pio PRIVATE pio_main.c)
# Add custom cmake commands if needed
# include(${PICO_SDK_PATH}/path/to/custom/commands.cmake)
 pico_sdk_init()
 pico_generate_pio_header(app ${PIO_FILE})

## alternate implementation

# find and build pioasm 

# include(${PICO_SDK_PATH}/tools/FindPioasm.cmake)

# set(PIO_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/7seg.pio")
# set(HEADER_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/generated_header.h")

# # Add custom command to process .pio file
# add_custom_command(
#     OUTPUT ${HEADER_FILE_PATH}
#     COMMAND ${Pioasm_EXECUTABLE}  ${PIO_FILE_PATH} ${HEADER_FILE_PATH}
#     DEPENDS ${PIO_FILE_PATH}
#     COMMENT "Generating header file from .pio file"
#     VERBATIM
# )
# target_sources(app PRIVATE ${HEADER_FILE_PATH})