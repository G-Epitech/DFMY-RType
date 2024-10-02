add_library(r-type_api_common_sdk SHARED)

add_subdirectory(src)

target_include_directories(r-type_api_common_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(r-type_api_common_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(r-type_api_common_sdk PRIVATE gcov)
endif ()
