cmake_minimum_required(VERSION 3.25)

add_library(MCU_RELATED
        system_stm32l4xx.c
        )

target_include_directories(MCU_RELATED PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ARM/CMSIS/Include)

