cmake_minimum_required(VERSION 3.25)

add_library(ST_RELATED
        system_stm32f4xx.c
        )

target_include_directories(ST_RELATED PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ARM/CMSIS/Include)

