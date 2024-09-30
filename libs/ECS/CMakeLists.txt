add_library(r-type_ECS_sdk SHARED)

add_subdirectory(src)

target_include_directories(r-type_ECS_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(r-type_ECS_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(r-type_network_sdk PRIVATE gcov)
endif ()
