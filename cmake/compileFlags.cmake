#Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_compile_options(-Wall -Wall -Wpedantic -g)

#Uncomment for software floating point
#add_compile_options(-mfloat-abi=soft)

set(ASM_FLAGS "-x assembler-with-cpp")
add_compile_options(-mcpu=${CPU_CORE} -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

add_compile_options(-Og -g)

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif ()

#set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/core/ST/${MCU_MODEL}/linker.ld)
#
#add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
#add_link_options(-mcpu=${CPU_CORE} -mthumb -mthumb-interwork)
#add_link_options(-T ${LINKER_SCRIPT})
