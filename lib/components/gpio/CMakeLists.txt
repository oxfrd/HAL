cmake_minimum_required(VERSION 3.25)

add_library(GPIO 
        # IGpioOutput.cpp 
        IPort.cpp
        IGpio.cpp)

target_link_libraries(GPIO PRIVATE MCU_RELATED MCU)

target_include_directories(GPIO PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/components/gpio
        ${CMAKE_SOURCE_DIR}/lib
)
 