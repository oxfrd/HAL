cmake_minimum_required(VERSION 3.25)

add_library(BMP280 
        BMP280.cpp
        )

target_link_libraries(BMP280 PRIVATE HAL_MODULES II2C)

target_include_directories(BMP280 PUBLIC .
                        PRIVATE ${HAL_DIR_PATH}/lib/components
                        PRIVATE ${HAL_DIR_PATH}/lib/components/i2c
                        )
 