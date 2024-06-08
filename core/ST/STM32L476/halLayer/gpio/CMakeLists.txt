cmake_minimum_required(VERSION 3.25)

add_library(GPIO_IMPLEMENTATION
        gpioPort.cpp
        gpioOutput.cpp
        gpioInput.cpp
        gpioAlternate.cpp
)

target_link_libraries(GPIO_IMPLEMENTATION PRIVATE HAL_MCU_LAYER MCU_RELATED)

target_include_directories(GPIO_IMPLEMENTATION PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer
        ${CMAKE_SOURCE_DIR}/lib/components/gpio
)
