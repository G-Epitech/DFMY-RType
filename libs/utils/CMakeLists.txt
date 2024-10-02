add_library(r-type_utils_sdk SHARED)

add_subdirectory(src)

target_include_directories(r-type_utils_sdk PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(r-type_utils_sdk PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(r-type_utils_sdk PRIVATE gcov)
endif ()
