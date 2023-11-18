cmake_minimum_required(VERSION 3.25)

add_library(HAL_MCU_LAYER nothing.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/components/mcu)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/components/gpio)

target_link_libraries(HAL_MCU_LAYER PUBLIC MCU_RELATED MCU GPIO)
