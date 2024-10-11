cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(r-type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(cmake/version.cmake)
include(cmake/platforms.cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

add_subdirectory(libs)
add_subdirectory(client)
add_subdirectory(server)

include(cmake/cpack/cpack.cmake)
