cmake_minimum_required(VERSION 3.25)

add_library(IUART 
        IUart.cpp
        )

target_link_libraries(IUART PRIVATE MCU_RELATED IMCU)

target_include_directories(IUART PUBLIC
        ${CMAKE_SOURCE_DIR}/lib/components/uart
        PRIVATE ${CMAKE_SOURCE_DIR}/lib/components/gpio
        PRIVATE ${CMAKE_SOURCE_DIR}/lib
)
 