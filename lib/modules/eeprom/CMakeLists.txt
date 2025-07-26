cmake_minimum_required(VERSION 3.25)

add_library(EEPROM_INTERFACE 
        IEeprom.cpp
        )

target_link_libraries(EEPROM_INTERFACE PRIVATE IMCU)

target_include_directories(EEPROM_INTERFACE PUBLIC .
                                PRIVATE )
 