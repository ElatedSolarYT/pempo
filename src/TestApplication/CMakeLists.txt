cmake_minimum_required(VERSION 3.2)
project(testapplication)

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")

set(SOURCE_FILES
        main.cpp main.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})