cmake_minimum_required(VERSION 3.25)

add_library(MCU_IMPLEMENTATION
        mcuInit.cpp
)
add_subdirectory(gpio)
add_subdirectory(timer)
add_subdirectory(interrupt)

target_link_libraries(MCU_IMPLEMENTATION PUBLIC 
                        HAL_MCU_LAYER 
                        MCU_RELATED 
                        GPIO_IMPLEMENTATION
                        TIMER_IMPLEMENTATION 
                        INTERRUPT_IMPLEMENTATION
                        )

target_include_directories(MCU_IMPLEMENTATION 
        PRIVATE ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        PUBLIC  ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/gpio
        PRIVATE  ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/timer
        PUBLIC  ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/halLayer/interrupt
        )
