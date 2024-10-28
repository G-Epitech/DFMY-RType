add_library(mew SHARED)

include(dependencies.cmake)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(include)

target_include_directories(mew PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(mew PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../..)
target_include_directories(mew PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(mew PRIVATE gcov)
endif ()
