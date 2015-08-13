cmake_minimum_required(VERSION 3.2)

###############################################
###             CONFIGURATION               ###
###############################################
set(ARCHITECTURE "x86_64")
if(ARCHITECTURE STREQUAL "x86_64")
    set(MONO_LIB_DIRECTORY "/usr/local/lib")
    set(MONO_ETC_DIRECTORY "/usr/local/lib")
    set(MONO_INCLUDE_DIRECTORY "/usr/local/include/mono-2.0")
elseif(ARCHITECTURE STREQUAL "i386")
    set(MONO_LIB_DIRECTORY "/opt/mono/lib")
    set(MONO_ETC_DIRECTORY "/opt/mono/etc")
    set(MONO_INCLUDE_DIRECTORY "/opt/mono/include/mono-2.0")
endif()
###############################################

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set(CMAKE_OSX_ARCHITECTURES ${ARCHITECTURE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# build osxinj via xcode
add_custom_command(
    OUTPUT osxinj
    WORKING_DIRECTORY ${EXT_DIR}/osxinj/osxinj
    COMMAND
        xcodebuild -target osxinj -arch ${ARCHITECTURE} -configuration ${CMAKE_BUILD_TYPE}
        CONFIGURATION_BUILD_DIR="${OUTPUT_DIR}" >
        /dev/null
)

# build bootstrap for osxinj via xcode
add_custom_command(
    OUTPUT bootstrap
    WORKING_DIRECTORY ${EXT_DIR}/osxinj/bootstrap
    COMMAND
        xcodebuild -target bootstrap -arch ${ARCHITECTURE} -configuration ${CMAKE_BUILD_TYPE}
        CONFIGURATION_BUILD_DIR="${OUTPUT_DIR}" >
        /dev/null
)

# build testapp for injecting via xcode
add_custom_command(
    OUTPUT testapp
    WORKING_DIRECTORY ${EXT_DIR}/osxinj/testapp
    COMMAND
        xcodebuild -target testapp -arch ${ARCHITECTURE} -configuration ${CMAKE_BUILD_TYPE}
        CONFIGURATION_BUILD_DIR="${OUTPUT_DIR}" >
        /dev/null
)

# Compile osxinj and boostrap
add_custom_target(build_osxinj ALL DEPENDS osxinj bootstrap testapp)

# mach_override
include_directories(${EXT_DIR}/mach_override/)
add_library(mach_override
    ${EXT_DIR}/mach_override/mach_override.c
    ${EXT_DIR}/mach_override/mach_override.h
    ${EXT_DIR}/mach_override/libudis86/input.c
    ${EXT_DIR}/mach_override/libudis86/input.h
    ${EXT_DIR}/mach_override/libudis86/syn.c
    ${EXT_DIR}/mach_override/libudis86/syn.h
    ${EXT_DIR}/mach_override/libudis86/udis86.c
    ${EXT_DIR}/mach_override/libudis86/syn-att.c
    ${EXT_DIR}/mach_override/libudis86/decode.c
    ${EXT_DIR}/mach_override/libudis86/decode.h
    ${EXT_DIR}/mach_override/libudis86/itab.c ${EXT_DIR}/mach_override/libudis86/itab.h
    ${EXT_DIR}/mach_override/libudis86/udint.h
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Bootstrap)
