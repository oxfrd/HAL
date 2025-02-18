cmake_minimum_required(VERSION 3.25)

add_library(IMCU 
        IMcu.cpp
        IComponent.cpp
)
target_link_libraries(IMCU PRIVATE MCU_RELATED)

target_include_directories(IMCU PUBLIC
        ${HAL_DIR_PATH}/lib/components/mcu
        ${HAL_DIR_PATH}/lib
)
 
