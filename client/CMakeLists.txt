set(CLIENT_CORE_LIB client_core)
set(CLIENT_EXECUTABLE r-type_client)

add_library(${CLIENT_CORE_LIB} STATIC)

target_include_directories(${CLIENT_CORE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CLIENT_CORE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(${CLIENT_EXECUTABLE} main.cpp)

include(dependencies.cmake)

target_link_libraries(${CLIENT_EXECUTABLE} PRIVATE ${CLIENT_CORE_LIB})

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${CLIENT_CORE_LIB} PRIVATE gcov)
endif ()

add_subdirectory(src)
add_subdirectory(tests)
