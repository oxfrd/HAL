cmake_minimum_required(VERSION 3.25)

add_library(IONEWIRE 
        IOneWire.cpp
        )

target_link_libraries(IONEWIRE PRIVATE MCU_RELATED IMCU)

target_include_directories(IONEWIRE PUBLIC
        ${HAL_DIR_PATH}/lib/components/oneWire
        PRIVATE ${HAL_DIR_PATH}/lib/components/gpio
        PRIVATE ${HAL_DIR_PATH}/lib
)
 