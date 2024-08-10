cmake_minimum_required(VERSION 3.25)

add_library(HAL_MODULES nothing.cpp)

add_subdirectory(sensors)

target_link_libraries(HAL_MODULES PUBLIC IMCU SENSORS)
