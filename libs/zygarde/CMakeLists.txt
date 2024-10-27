add_library(zygarde SHARED)

add_subdirectory(src)
add_subdirectory(includes)
add_subdirectory(tests)

target_include_directories(zygarde PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(zygarde PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../..)

include(dependencies.cmake)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(zygarde PRIVATE gcov)
endif ()
