cmake_minimum_required(VERSION 3.25)

add_library(GPIO
        gpio.cpp
        IPort.cpp
)

target_link_libraries(GPIO PRIVATE MCU_RELATED)

target_include_directories(GPIO PUBLIC
        ./inc
        ${CMAKE_SOURCE_DIR}/lib/
        ${CMAKE_SOURCE_DIR}/lib/interface

)

