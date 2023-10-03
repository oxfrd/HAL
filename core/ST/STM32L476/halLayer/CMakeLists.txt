cmake_minimum_required(VERSION 3.25)

add_library(MCU_IMPLEMENTATION
        port.cpp
        gpio.cpp
)

target_link_libraries(MCU_IMPLEMENTATION PRIVATE HAL)

target_include_directories(MCU_IMPLEMENTATION PUBLIC
        ./
        ${CMAKE_SOURCE_DIR}/lib/components/gpio
        ${CMAKE_SOURCE_DIR}/lib/components/mcu
        ${CMAKE_SOURCE_DIR}/lib/interface
)
