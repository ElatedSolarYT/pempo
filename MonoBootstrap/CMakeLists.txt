cmake_minimum_required(VERSION 3.2)
project(monobootstrap)

set(MONO_LIB_DIRECTORY_X86_64 "/usr/local/lib")
set(MONO_ETC_DIRECTORY_X86_64 "/usr/local/lib")
set(MONO_INCLUDE_DIRECTORY_X86_64 "/usr/local/include/mono-2.0")
set(MONO_LIB_DIRECTORY_X86 "/opt/mono/lib")
set(MONO_ETC_DIRECTORY_X86 "/opt/mono/etc")
set(MONO_INCLUDE_DIRECTORY_X86 "/opt/mono/include/mono-2.0")

add_definitions(-DMONO_LIB_DIRECTORY_X86_64=${MONO_LIB_DIRECTORY_X86_64})
add_definitions(-DMONO_ETC_DIRECTORY_X86_64=${MONO_ETC_DIRECTORY_X86_64})
add_definitions(-DMONO_LIB_DIRECTORY_X86=${MONO_LIB_DIRECTORY_X86})
add_definitions(-DMONO_ETC_DIRECTORY_X86=${MONO_ETC_DIRECTORY_X86})

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

set(SOURCE_FILES
    main.cpp main.h)

# i386
set(CMAKE_OSX_ARCHITECTURES "i386")
add_library(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} PUBLIC ${MONO_INCLUDE_DIRECTORY_X86})

target_link_libraries(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} mach_override ${MONO_LIB_DIRECTORY_X86}/libmono-2.0.dylib ${MONO_LIB_DIRECTORY_X86}/libmonosgen-2.0.dylib -lpthread)

# x86_64
set(CMAKE_OSX_ARCHITECTURES "x86_64")
add_library(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} PUBLIC ${MONO_INCLUDE_DIRECTORY_X86})

target_link_libraries(${PROJECT_NAME}_${CMAKE_OSX_ARCHITECTURES} mach_override ${MONO_LIB_DIRECTORY_X86_64}/libmono-2.0.dylib ${MONO_LIB_DIRECTORY_X86_64}/libmonosgen-2.0.dylib -lpthread)

# build
add_custom_target(${PROJECT_NAME} DEPENDS ${PROJECT_NAME}_i386 ${PROJECT_NAME}_x86_64)
