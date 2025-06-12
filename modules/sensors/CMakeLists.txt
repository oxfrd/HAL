cmake_minimum_required(VERSION 3.25)

add_library(BMP280 
        BMP280.cpp
        DS18B20.cpp
        )

target_link_libraries(BMP280 PRIVATE HAL_MODULES II2C IONEWIRE ITIMER)

target_include_directories(BMP280 PUBLIC .
                        PRIVATE ${HAL_DIR_PATH}/lib/components
                        PRIVATE ${HAL_DIR_PATH}/lib/components/i2c
                        PRIVATE ${HAL_DIR_PATH}/lib/components/oneWire
                        PRIVATE ${HAL_DIR_PATH}/lib/components/timer
                        )
 