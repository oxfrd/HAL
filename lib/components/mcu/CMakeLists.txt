cmake_minimum_required(VERSION 3.25)

add_library(MCU
        IMcu.cpp
)

target_link_libraries(MCU PRIVATE MCU_RELATED)

target_include_directories(MCU PUBLIC
        ./*.h
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/lib/interface
)

