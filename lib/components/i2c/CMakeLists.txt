cmake_minimum_required(VERSION 3.25)

add_library(II2C 
        II2c.cpp
        )

target_link_libraries(II2C PRIVATE MCU_RELATED IMCU)

target_include_directories(IUART PUBLIC
        ${HAL_DIR_PATH}/lib/components/i2c
        PRIVATE ${HAL_DIR_PATH}/lib/components/gpio
        PRIVATE ${HAL_DIR_PATH}/lib
)
 