cmake_minimum_required(VERSION 3.25)

add_library(EEPROM 
        24Cxx.cpp
        )

target_link_libraries(EEPROM PRIVATE HAL_MODULES II2C ITIMER)

target_include_directories(EEPROM PUBLIC .
                        PRIVATE ${HAL_DIR_PATH}/lib/components
                        PRIVATE ${HAL_DIR_PATH}/lib/components/i2c
                        PRIVATE ${HAL_DIR_PATH}/lib/components/timer
                        )
 