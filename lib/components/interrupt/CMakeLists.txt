cmake_minimum_required(VERSION 3.25)

add_library(IINTERRUPT 
        ITimeInterrupt.cpp
        IInterrupt.cpp
        )

target_link_libraries(IINTERRUPT PRIVATE MCU_RELATED IMCU)

target_include_directories(IINTERRUPT PRIVATE
        ${HAL_DIR_PATH}/lib
        ${HAL_DIR_PATH}/lib/components/interrupt
)
 