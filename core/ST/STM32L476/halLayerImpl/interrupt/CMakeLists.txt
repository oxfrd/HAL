cmake_minimum_required(VERSION 3.25)

add_library(INTERRUPT_IMPLEMENTATION
        timeInterrupt.cpp
        interrupt.cpp
)

target_link_libraries(INTERRUPT_IMPLEMENTATION PRIVATE HAL_MCU_LAYER MCU_RELATED)

target_include_directories(INTERRUPT_IMPLEMENTATION 
        PUBLIC ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayerImpl/timer
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/components/interrupt
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/components/timer
)
