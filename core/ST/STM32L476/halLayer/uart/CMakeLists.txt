cmake_minimum_required(VERSION 3.25)

add_library(UART_IMPLEMENTATION
        uart.cpp
)

target_include_directories(UART_IMPLEMENTATION PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/gpio
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/interrupt
        PUBLIC ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/uart
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/utils
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/components/interrupt
        
)

target_link_libraries(UART_IMPLEMENTATION PUBLIC HAL_MCU_LAYER MCU_RELATED HAL_UTILS)
