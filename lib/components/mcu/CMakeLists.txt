cmake_minimum_required(VERSION 3.25)

add_library(IMCU 
        IMcu.cpp
        IComponent.cpp
)
target_link_libraries(IMCU PRIVATE MCU_RELATED)

target_include_directories(IMCU PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/components/mcu
        ${CMAKE_SOURCE_DIR}/lib
)
 
