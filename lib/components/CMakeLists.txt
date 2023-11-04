cmake_minimum_required(VERSION 3.25)

add_library(HAL STATIC nothing.cpp
        ../interface/IComponent.h)

list(APPEND HAL_SOURCES gpio )

add_subdirectory(${HAL_SOURCES})

foreach (item IN LISTS HAL_SOURCES)
    string(TOUPPER ${item} uppercaseItem)
    target_link_libraries(HAL PUBLIC ${uppercaseItem})
endforeach ()

target_link_libraries(HAL PUBLIC MCU_RELATED)
