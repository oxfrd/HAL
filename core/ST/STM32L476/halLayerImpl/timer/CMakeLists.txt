cmake_minimum_required(VERSION 3.25)

add_library(TIMER_IMPLEMENTATION
        timer.cpp
)

target_link_libraries(TIMER_IMPLEMENTATION PRIVATE HAL_MCU_LAYER MCU_RELATED)

target_include_directories(TIMER_IMPLEMENTATION PRIVATE
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayerImpl
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/components/timer
)
