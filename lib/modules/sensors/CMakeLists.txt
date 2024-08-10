cmake_minimum_required(VERSION 3.25)

add_library(SENSORS 
        ILightSensor.cpp
        IPressureSensor.cpp
        )

target_link_libraries(SENSORS PRIVATE IMCU)

target_include_directories(SENSORS PUBLIC .
                                PRIVATE )
 