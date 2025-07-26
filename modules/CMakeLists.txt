cmake_minimum_required(VERSION 3.25)

add_library(MODULES_IMPL nothing.cpp)

add_subdirectory(sensors)
add_subdirectory(eeprom)

target_link_libraries(MODULES_IMPL  PUBLIC BMP280 EEPROM)
