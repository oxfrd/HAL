cmake_minimum_required(VERSION 3.25)

add_library(HAL nothing.cpp)

list(APPEND HAL_SOURCES gpio)

add_subdirectory(${HAL_SOURCES} 
    ${CMAKE_SOURCE_DIR}/lib/components/mcu)

# foreach (item IN LISTS HAL_SOURCES)
#     string(TOUPPER ${item} uppercaseItem)
#     target_link_libraries(HAL PUBLIC ${uppercaseItem})
# endforeach ()

target_link_libraries(HAL PUBLIC MCU_RELATED GPIO FGH)
