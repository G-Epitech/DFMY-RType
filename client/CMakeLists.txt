set(CLIENT_CORE_LIB r-type_client_core)
set(CLIENT_EXECUTABLE r-type_client)

add_library(${CLIENT_CORE_LIB} STATIC)

target_include_directories(${CLIENT_CORE_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${CLIENT_CORE_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(${CLIENT_CORE_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../)

if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_executable(${CLIENT_EXECUTABLE} main.cpp)
    else ()
        add_executable(${CLIENT_EXECUTABLE} WIN32 main.cpp ../r-type.rc)
    endif ()
else ()
    add_executable(${CLIENT_EXECUTABLE} main.cpp)
    set_target_properties(${CLIENT_EXECUTABLE} PROPERTIES
            INSTALL_RPATH "$ORIGIN")
endif ()

include(dependencies.cmake)

target_link_libraries(${CLIENT_EXECUTABLE} PRIVATE ${CLIENT_CORE_LIB})

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${CLIENT_CORE_LIB} PRIVATE gcov)
endif ()

add_subdirectory(src)
add_subdirectory(tests)

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})