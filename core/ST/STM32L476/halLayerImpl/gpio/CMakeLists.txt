cmake_minimum_required(VERSION 3.25)

add_library(GPIO_IMPLEMENTATION
        gpioPort.cpp
        gpioOutput.cpp
        gpioInput.cpp
        gpioAlternate.cpp
)

target_link_libraries(GPIO_IMPLEMENTATION PRIVATE HAL_MCU_LAYER MCU_RELATED)

target_include_directories(GPIO_IMPLEMENTATION PRIVATE
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/Include
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl
        ${HAL_DIR_PATH}/lib/components/gpio
)
