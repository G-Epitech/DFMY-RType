add_library(r-type_network_common SHARED)

add_subdirectory(src)

target_include_directories(r-type_network_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(r-type_network_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
