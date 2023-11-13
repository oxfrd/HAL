cmake_minimum_required(VERSION 3.25)

add_library(MCU_IMPLEMENTATION
        gpioPort.cpp
        gpio.cpp
        mcuInit.cpp
)

target_link_libraries(MCU_IMPLEMENTATION PUBLIC HAL MCU_RELATED)

target_include_directories(MCU_IMPLEMENTATION PUBLIC
        ./Include
        ./
        ${CMAKE_SOURCE_DIR}/lib/components/gpio
        ${CMAKE_SOURCE_DIR}/lib/components/mcu
        ${CMAKE_SOURCE_DIR}/lib/interface
)
