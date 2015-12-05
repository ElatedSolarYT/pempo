cmake_minimum_required(VERSION 3.2)
project(injector)

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")

set(MACH_INJECT_DIRECTORY ${EXT_DIR}/mach_inject/mach_inject)
include_directories(${MACH_INJECT_DIRECTORY})

set(SOURCE_FILES
        ${MACH_INJECT_DIRECTORY}/mach_inject.c ${MACH_INJECT_DIRECTORY}/mach_inject.h
        main.cpp main.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0)
target_link_libraries(${PROJECT_NAME})