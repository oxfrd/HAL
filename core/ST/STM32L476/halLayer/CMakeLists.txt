cmake_minimum_required(VERSION 3.25)

add_library(MCU_IMPLEMENTATION
        gpioPort.cpp
        gpio.cpp
        mcuInit.cpp
)

target_link_libraries(MCU_IMPLEMENTATION PRIVATE HAL_MCU_LAYER MCU_RELATED)

target_include_directories(MCU_IMPLEMENTATION PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer
)
