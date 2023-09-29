cmake_minimum_required(VERSION 3.25)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(MCU_MODEL STM32L476)

include(${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/cfg.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/toolchain_arm.cmake)
include(./cmake/compileFlags.cmake)

# project settings
project(HAL VERSION 1.0 LANGUAGES C CXX ASM)


message(STATUS "")
message(STATUS "########################################")
message(STATUS "### PROJECT:    " ${PROJECT_NAME})
message(STATUS "### MCU MODEL:  " ${MCU_MODEL})
message(STATUS "### CPU MODEL:  " ${CPU_CORE})
message(STATUS "### VERSION:    " ${PROJECT_VERSION})
message(STATUS "########################################")
message(STATUS "")

add_definitions(-DDEBUG -D${MCU_MODEL})

add_subdirectory(core)
add_subdirectory(lib/components)

file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Startup/*.*"
#        "${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Source/system_stm32l4xx.c"
        "${CMAKE_SOURCE_DIR}/Src/main.cpp"
        )

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/linker.ld)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=${CPU_CORE} -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

set(TARGET_NAME ${PROJECT_NAME}.elf)
add_executable(${TARGET_NAME} ${SOURCES} ${LINKER_SCRIPT})

target_link_libraries(${TARGET_NAME} PRIVATE MCU_RELATED HAL)

target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Inc
        ${CMAKE_SOURCE_DIR}/core/ARM/CMSIS/Include
        ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/Include
        ${CMAKE_SOURCE_DIR}/lib/
        ${CMAKE_SOURCE_DIR}/lib/interface)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
                 Building ${BIN_FILE}")
