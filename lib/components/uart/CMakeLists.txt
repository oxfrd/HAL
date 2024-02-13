cmake_minimum_required(VERSION 3.25)

add_library(IUART 
        IUart.cpp
        )

target_link_libraries(IUART PRIVATE MCU_RELATED IMCU)

target_include_directories(IUART PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/components/uart
        ${CMAKE_SOURCE_DIR}/lib/components/gpio
        ${CMAKE_SOURCE_DIR}/lib
)
 