cmake_minimum_required(VERSION 3.25)

add_library(I2C_IMPLEMENTATION
        i2c.cpp
)

target_include_directories(I2C_IMPLEMENTATION PRIVATE
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/Include
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl/gpio
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl/interrupt
        PUBLIC ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl/i2c
        PUBLIC ${HAL_DIR_PATH}/lib/utils
        PUBLIC ${HAL_DIR_PATH}/lib/components/interrupt    
)

target_link_libraries(I2C_IMPLEMENTATION PUBLIC HAL_MCU_LAYER MCU_RELATED HAL_UTILS)
