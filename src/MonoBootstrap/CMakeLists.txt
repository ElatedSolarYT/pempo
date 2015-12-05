cmake_minimum_required(VERSION 3.2)
project(monobootstrap)

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

set(SOURCE_FILES
    main.cpp main.h)

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

find_library(MONO_FRAMEWORK Mono)

target_include_directories(${PROJECT_NAME} PUBLIC ${MONO_FRAMEWORK}/Headers/mono-2.0)
target_link_libraries(${PROJECT_NAME} ${MONO_FRAMEWORK}/Libraries/libmonosgen-2.0.dylib -lpthread -liconv -lobjc)
