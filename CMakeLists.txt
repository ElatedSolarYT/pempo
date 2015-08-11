cmake_minimum_required(VERSION 3.2)
project(pempo)

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE -arch i386")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11 -arch i386")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# build osxinj via xcode
add_custom_command(
    OUTPUT osxinj
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ext/osxinj/osxinj
    COMMAND
        xcodebuild -target osxinj -configuration ${CMAKE_BUILD_TYPE} CONFIGURATION_BUILD_DIR="${OUTPUT_DIR}" > /dev/null
)

# build bootstrap for osxinj via xcode
add_custom_command(
    OUTPUT bootstrap
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ext/osxinj/bootstrap
    COMMAND
        xcodebuild -target bootstrap -configuration ${CMAKE_BUILD_TYPE} CONFIGURATION_BUILD_DIR="${OUTPUT_DIR}" >
        /dev/null
)

# build testapp for injecting via xcode
add_custom_command(
    OUTPUT testapp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ext/osxinj/testapp
    COMMAND
        xcodebuild -target testapp -configuration ${CMAKE_BUILD_TYPE} CONFIGURATION_BUILD_DIR="${OUTPUT_DIR}" >
        /dev/null
)

link_directories("/opt/mono/lib")
include_directories("/opt/mono/include/mono-2.0")

set(SOURCE_FILES main.cpp)
add_library(pempo SHARED ${SOURCE_FILES})
target_link_libraries(pempo "-lmono-2.0" "-lmonosgen-2.0" "-lpthread" "-framework Foundation")

# Compile osxinj and boostrap
add_custom_target(build_osxinj ALL DEPENDS osxinj bootstrap testapp)
