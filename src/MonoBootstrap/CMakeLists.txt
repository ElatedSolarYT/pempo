cmake_minimum_required(VERSION 3.2)
project(monobootstrap)

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")

find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
find_library(MONO_FRAMEWORK Mono)

set(SOURCE_FILES
    main.cpp main.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0)
target_include_directories(${PROJECT_NAME} PUBLIC ${MONO_FRAMEWORK}/Headers/mono-2.0)
target_link_libraries(${PROJECT_NAME} ${COREFOUNDATION_FRAMEWORK} ${MONO_FRAMEWORK}/Libraries/libmonosgen-2.0.dylib -lpthread -liconv -lobjc)
