cmake_minimum_required(VERSION 3.25)

add_library(FGH 
        IMcu.cpp
        IComponent.cpp
)
target_link_libraries(FGH PRIVATE MCU_RELATED GPIO)


target_include_directories(FGH PUBLIC
        ./
        ${CMAKE_SOURCE_DIR}/lib
)
 
