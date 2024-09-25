add_library(r-type_network_sdk SHARED)

add_subdirectory(src)
add_subdirectory(tests)

target_include_directories(r-type_network_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(r-type_network_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
