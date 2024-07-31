cmake_minimum_required(VERSION 3.13)

# Initialize the SDK
include(pico_sdk_import.cmake)

project(oled_display C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add the executable
add_executable(oled_display
    main.c
)

target_sources(oled_display PRIVATE 
    display/oled.c
    display/text.c
)

target_include_directories(oled_display PRIVATE fonts display)
include_directories(fonts display)

# Add the pico_stdlib library which includes commonly used libraries like hardware_spi
target_link_libraries(oled_display pico_stdlib hardware_spi)

# Enable usb output, disable uart output
pico_enable_stdio_usb(oled_display 0)
pico_enable_stdio_uart(oled_display 1)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(oled_display)
