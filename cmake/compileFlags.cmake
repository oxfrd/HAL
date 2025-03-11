#Uncomment for hardware floating point
# add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
# add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
# add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
# add_compile_options(-Wall -Wall -Wpedantic -g)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wall -Wpedantic -g" CACHE STRING "C Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wall -Wpedantic -g" CACHE STRING "C++ Compiler Flags" FORCE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING" CACHE STRING "C Compiler Definitions" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING" CACHE STRING "C++ Compiler Definitions" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mfloat-abi=hard -mfpu=fpv4-sp-d16" CACHE STRING "Linker Flags" FORCE)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)

# set(ASM_FLAGS "-x assembler-with-cpp" CACHE STRING "asm flags")
# add_compile_options(-mcpu=${CPU_CORE} -mthumb -mthumb-interwork)
# add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=${CPU_CORE} -mthumb -mthumb-interwork" CACHE STRING "C Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=${CPU_CORE} -mthumb -mthumb-interwork" CACHE STRING "CXX Compiler Flags" FORCE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections -fno-common -fmessage-length=0" CACHE STRING "C Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections -fno-common -fmessage-length=0" CACHE STRING "CXX Compiler Flags" FORCE)


# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp" CACHE STRING "ASM Compiler Flags" FORCE)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Ustawiam optymalizację: -Ofast")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast" CACHE STRING "C Flags" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast" CACHE STRING "CXX Flags" FORCE)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Ustawiam optymalizację: -Ofast -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Ofast -g" CACHE STRING "C Flags" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -g" CACHE STRING "CXX Flags" FORCE)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Ustawiam optymalizację: -Os")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os" CACHE STRING "C Flags" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os" CACHE STRING "CXX Flags" FORCE)
else()
    message(STATUS "Ustawiam minimalną optymalizację: -Og -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -g" CACHE STRING "C Flags" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -g" CACHE STRING "CXX Flags" FORCE)
endif()



set(LINKER_SCRIPT ${HAL_DIR_PATH}/core/${MANUFACTURER}/${MCU_MODEL}/linker.ld CACHE STRING "Linker")

