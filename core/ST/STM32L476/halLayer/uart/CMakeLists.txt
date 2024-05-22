cmake_minimum_required(VERSION 3.25)

add_library(UART_IMPLEMENTATION
        uart.cpp
)

target_link_libraries(UART_IMPLEMENTATION PRIVATE HAL_MCU_LAYER MCU_RELATED)

target_include_directories(UART_IMPLEMENTATION PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/gpio
)
