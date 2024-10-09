add_library(abra SHARED)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(includes)

target_include_directories(abra PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(abra PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

include(dependencies.cmake)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(abra  PRIVATE gcov)
endif ()
