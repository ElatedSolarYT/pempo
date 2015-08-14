cmake_minimum_required(VERSION 3.2)
project(bootstrap)

list(APPEND CMAKE_C_FLAGS)
list(APPEND CMAKE_CXX_FLAGS -std=c++11)

find_library(COCOA_LIBRARY Cocoa)
find_library(APP_SERVICES_LIBRARY ApplicationServices)

set(SOURCE_FILES
    main.cpp main.h)
add_library(bootstrap SHARED ${SOURCE_FILES})
target_link_libraries(bootstrap ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})