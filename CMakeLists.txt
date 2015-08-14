cmake_minimum_required(VERSION 3.2)

###############################################
###             CONFIGURATION               ###
###############################################
set(ARCHITECTURE "x86_64")
###############################################

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set(CMAKE_OSX_ARCHITECTURES ${ARCHITECTURE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# build mono library via mono
add_custom_command(
    OUTPUT monolib
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MonoLibrary
    COMMAND xbuild > /dev/null
)

# Compile Mono library
add_custom_target(build_monolib ALL DEPENDS monolib)

# mach_inject
set(MACH_INJECT_DIRECTORY ${EXT_DIR}/mach_inject/mach_inject)
include_directories(${MACH_INJECT_DIRECTORY})
add_library(mach_inject
    ${MACH_INJECT_DIRECTORY}/mach_inject.c ${MACH_INJECT_DIRECTORY}/mach_inject.h
)

# mach_override
set(MACH_OVERRIDE_DIRECTORY ${EXT_DIR}/mach_override)
include_directories(${MACH_OVERRIDE_DIRECTORY})
add_library(mach_override
    ${MACH_OVERRIDE_DIRECTORY}/mach_override.c ${MACH_OVERRIDE_DIRECTORY}/mach_override.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/input.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/input.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/syn.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/syn.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/udis86.c
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/syn-att.c
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/decode.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/decode.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/itab.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/itab.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/udint.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Bootstrap)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Injector)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/MonoBootstrap)
