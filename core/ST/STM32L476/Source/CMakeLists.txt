cmake_minimum_required(VERSION 3.25)

if (NOT DEFINED HAL_DIR_PATH)
        message(FATAL_ERROR "HAL_DIR_PATH not specified")
endif()

add_library(MCU_RELATED
        system_stm32l4xx.c
        ../Startup/startup_stm32l476xx.s
        )

target_link_libraries(MCU_RELATED PRIVATE HAL_MCU_LAYER)

target_include_directories(MCU_RELATED PUBLIC
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/Include
        ${HAL_DIR_PATH}/core/ARM/CMSIS/Include
        ${HAL_DIR_PATH}/core/ST/${MCU_MODEL}/halLayerImpl
        ${HAL_DIR_PATH}/lib/components
)

