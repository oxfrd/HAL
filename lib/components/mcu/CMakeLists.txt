cmake_minimum_required(VERSION 3.25)

add_library(MCU 
        IMcu.cpp
        IComponent.cpp
)
target_link_libraries(MCU PRIVATE MCU_RELATED)

target_include_directories(MCU PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/components/mcu
        ${CMAKE_SOURCE_DIR}/lib
)
 
