add_library(r-type_ECS_sdk SHARED)

add_subdirectory(src)

target_include_directories(r-type_ECS_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(r-type_ECS_sdk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set_target_properties(r-type_ECS_sdk PROPERTIES LINKER_LANGUAGE CXX)
