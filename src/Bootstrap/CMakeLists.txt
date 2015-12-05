cmake_minimum_required(VERSION 3.2)
project(bootstrap)

find_library(COCOA_LIBRARY Cocoa)
find_library(APP_SERVICES_LIBRARY ApplicationServices)

set(SOURCE_FILES
    main.cpp main.h)

set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})