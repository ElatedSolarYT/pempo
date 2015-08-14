cmake_minimum_required(VERSION 3.2)
project(monobootstrap)

if(ARCHITECTURE STREQUAL "x86_64")
    set(MONOBOOTSTRAP_LIB_DIRECTORY "/usr/local/lib")
    set(MONOBOOTSTRAP_ETC_DIRECTORY "/usr/local/lib")
    set(MONOBOOTSTRAP_INCLUDE_DIRECTORY "/usr/local/include/mono-2.0")
elseif(ARCHITECTURE STREQUAL "i386")
    set(MONOBOOTSTRAP_LIB_DIRECTORY "/opt/mono/lib")
    set(MONOBOOTSTRAP_ETC_DIRECTORY "/opt/mono/etc")
    set(MONOBOOTSTRAP_INCLUDE_DIRECTORY "/opt/mono/include/mono-2.0")
endif()

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

include_directories(${MONOBOOTSTRAP_INCLUDE_DIRECTORY})
link_directories(${MONOBOOTSTRAP_LIB_DIRECTORY})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
    main.cpp main.h)
add_library(monobootstrap SHARED ${SOURCE_FILES})
target_link_libraries(monobootstrap mach_override -lmono-2.0 -lmonosgen-2.0 -lpthread)