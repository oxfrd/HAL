cmake_minimum_required(VERSION 3.25)

add_library(HAL_UTILS
                 circularBuffer.cpp)

target_include_directories(HAL_UTILS 
         PUBLIC ${HAL_DIR_PATH}/lib/utils
         )
