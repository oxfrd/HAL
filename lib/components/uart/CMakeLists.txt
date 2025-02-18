cmake_minimum_required(VERSION 3.25)

add_library(IUART 
        IUart.cpp
        )

target_link_libraries(IUART PRIVATE MCU_RELATED IMCU)

target_include_directories(IUART PUBLIC
        ${HAL_DIR_PATH}/lib/components/uart
        PRIVATE ${HAL_DIR_PATH}/lib/components/gpio
        PRIVATE ${HAL_DIR_PATH}/lib
)
 