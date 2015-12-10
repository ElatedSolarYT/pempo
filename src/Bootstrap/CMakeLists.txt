cmake_minimum_required(VERSION 3.2)
project(bootstrap)

find_library(COCOA_LIBRARY Cocoa)
find_library(APP_SERVICES_LIBRARY ApplicationServices)

set(MACH_OVERRIDE_DIRECTORY ${EXT_DIR}/mach_override)

set(SOURCE_FILES
    main.cpp main.h
    ${MACH_OVERRIDE_DIRECTORY}/mach_override.c ${MACH_OVERRIDE_DIRECTORY}/mach_override.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/input.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/input.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/syn.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/syn.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/udis86.c
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/syn-att.c
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/decode.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/decode.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/itab.c ${MACH_OVERRIDE_DIRECTORY}/libudis86/itab.h
    ${MACH_OVERRIDE_DIRECTORY}/libudis86/udint.h)

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")

include_directories(${MACH_OVERRIDE_DIRECTORY})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})