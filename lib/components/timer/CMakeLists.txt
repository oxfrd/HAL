cmake_minimum_required(VERSION 3.25)

add_library(ITIMER 
        ITimer.cpp
        )

target_link_libraries(ITIMER PRIVATE MCU_RELATED IMCU)

target_include_directories(ITIMER PRIVATE
        ${HAL_DIR_PATH}/lib
)
 