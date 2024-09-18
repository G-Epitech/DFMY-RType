cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
project(rtype)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
