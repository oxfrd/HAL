cmake_minimum_required(VERSION 3.25)

add_library(IINTERRUPT 
        ITimeInterrupt.cpp
        )

target_link_libraries(IINTERRUPT PRIVATE MCU_RELATED IMCU)

target_include_directories(IINTERRUPT PRIVATE
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/lib/components/interrupt
)
 