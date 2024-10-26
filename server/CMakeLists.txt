set(SERVER_CORE_LIB r-type_server_core)
set(SERVER_EXECUTABLE r-type_server)

add_library(${SERVER_CORE_LIB} STATIC)

target_include_directories(${SERVER_CORE_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${SERVER_CORE_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../)
target_include_directories(${SERVER_CORE_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/)

if (WIN32)
    add_executable(${SERVER_EXECUTABLE} main.cpp ../r-type.rc)
else ()
    add_executable(${SERVER_EXECUTABLE} main.cpp)
    set_target_properties(${SERVER_EXECUTABLE} PROPERTIES
            INSTALL_RPATH "$ORIGIN")
endif ()

include(dependencies.cmake)

target_link_libraries(${SERVER_EXECUTABLE} PRIVATE ${SERVER_CORE_LIB})

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${SERVER_CORE_LIB} PRIVATE gcov)
endif ()

add_subdirectory(src)
add_subdirectory(tests)

include(commands.cmake)
