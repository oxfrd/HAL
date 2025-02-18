cmake_minimum_required(VERSION 3.25)

add_library(IGPIO 
        IGpio.cpp
        IPort.cpp
        IGpioOutput.cpp
        IGpioInput.cpp
        IGpioAlternate.cpp
        )

target_link_libraries(IGPIO PRIVATE MCU_RELATED IMCU)

target_include_directories(IGPIO PUBLIC
        ${HAL_DIR_PATH}/lib/components/gpio
        ${HAL_DIR_PATH}/lib
)
 