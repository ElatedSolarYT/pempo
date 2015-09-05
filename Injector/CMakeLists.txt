cmake_minimum_required(VERSION 3.2)
project(injector)

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

include_directories(${MONO_INCLUDE_DIRECTORY})
link_directories(${MONO_LIB_DIRECTORY})

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")

set(SOURCE_FILES
    main.cpp main.h)

add_executable(injector ${SOURCE_FILES})
target_link_libraries(injector mach_inject)