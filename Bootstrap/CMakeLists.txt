cmake_minimum_required(VERSION 3.2)
project(Bootstrap)

list(APPEND CMAKE_C_FLAGS "-D_THREAD_SAFE")
list(APPEND CMAKE_CXX_FLAGS "-D_THREAD_SAFE -std=c++11")

include_directories(${MONO_INCLUDE_DIRECTORY})
link_directories(${MONO_LIB_DIRECTORY})

find_package(OpenGL REQUIRED)
find_library(APP_SERVICES_LIBRARY ApplicationServices)
find_library(CARBON_LIBRARY Carbon)

configure_file(cmake_vars.h ${CMAKE_CURRENT_SOURCE_DIR}/cmake_vars_generated.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
    main.cpp main.h)
add_library(pempo SHARED ${SOURCE_FILES} cmake_vars.h)
target_link_libraries(pempo mach_override ${APP_SERVICES_LIBRARY} ${OPENGL_LIBRARIES} "-lmono-2.0" "-lmonosgen-2.0"
"-lpthread" "-framework Foundation" "-framework QuartzCore" ${CARBON_LIBRARY})