# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(main C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(main_executable 
    app/main.c 
    drivers/ssd1306_i2c.c 
    drivers/rp2040.c 
    hal/adc_temp.c
)

# Add the standard library to the build
target_link_libraries(main_executable
        hardware_adc
        hardware_i2c
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(main_executable PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(main_executable 0)
pico_enable_stdio_usb(main_executable 1)

pico_add_extra_outputs(main_executable)

# Executável de teste

add_executable(unit_test_executable 
    test/test_adc_temp.c
    drivers/ssd1306_i2c.c 
    drivers/rp2040.c 
    hal/adc_temp.c
    test/unity/unity.c
)

# Add the standard library to the build
target_link_libraries(unit_test_executable
        hardware_adc
        hardware_i2c
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(unit_test_executable PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}
)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(unit_test_executable 0)
pico_enable_stdio_usb(unit_test_executable 1)

pico_add_extra_outputs(unit_test_executable)
