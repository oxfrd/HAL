cmake_minimum_required(VERSION 3.25)

add_library(HAL_MCU_LAYER nothing.cpp)

add_subdirectory(${HAL_DIR_PATH}/lib/components/mcu)
add_subdirectory(${HAL_DIR_PATH}/lib/components/gpio)
add_subdirectory(${HAL_DIR_PATH}/lib/components/uart)
add_subdirectory(${HAL_DIR_PATH}/lib/components/timer)
add_subdirectory(${HAL_DIR_PATH}/lib/components/interrupt)
add_subdirectory(${HAL_DIR_PATH}/lib/components/i2c)

target_link_libraries(HAL_MCU_LAYER PUBLIC MCU_RELATED IMCU IGPIO IUART ITIMER IINTERRUPT II2C)
