cmake_minimum_required(VERSION 3.25)

add_library(UART_IMPLEMENTATION
        uart.cpp
)

target_include_directories(UART_IMPLEMENTATION PRIVATE
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/Include
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl/gpio
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl/interrupt
        PUBLIC ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl/uart
        PUBLIC ${HAL_DIR_PATH}/lib/utils
        PUBLIC ${HAL_DIR_PATH}/lib/components/interrupt
        
)

target_link_libraries(UART_IMPLEMENTATION PUBLIC HAL_MCU_LAYER MCU_RELATED HAL_UTILS)
