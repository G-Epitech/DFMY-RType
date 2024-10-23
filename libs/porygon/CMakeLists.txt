add_library(porygon SHARED)

add_subdirectory(src)
add_subdirectory(tests)

target_include_directories(porygon PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(porygon PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(porygon PRIVATE gcov)
endif ()
