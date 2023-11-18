cmake_minimum_required(VERSION 3.25)

add_library(MCU_RELATED
        system_stm32l4xx.c
        )

target_link_libraries(MCU_RELATED PRIVATE HAL_MCU_LAYER)

target_include_directories(MCU_RELATED PUBLIC
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ARM/CMSIS/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer
        ${CMAKE_SOURCE_DIR}/lib/components

)

