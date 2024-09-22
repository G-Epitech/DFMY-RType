set(SERVER_CORE_LIB r-type_server_core)
set(SERVER_EXECUTABLE r-type_server)

add_library(${SERVER_CORE_LIB} STATIC)

target_include_directories(${SERVER_CORE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${SERVER_CORE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(${SERVER_EXECUTABLE} main.cpp)

include(dependencies.cmake)

target_link_libraries(${SERVER_EXECUTABLE} ${SERVER_CORE_LIB})

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${SERVER_CORE_LIB} gcov)
endif ()

add_subdirectory(src)
