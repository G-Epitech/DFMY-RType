cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(rtype)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(cmake/version.cmake)
include(cmake/platforms.cmake)

add_subdirectory(libs)
add_subdirectory(client)
add_subdirectory(server)

include(cmake/cpack/cpack.cmake)
