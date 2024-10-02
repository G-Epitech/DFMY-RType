set(SDK_API_COMMON ${CMAKE_PROJECT_NAME}_api_common_sdk)

add_library(${SDK_API_COMMON} SHARED)

include(dependencies.cmake)

add_subdirectory(src)

target_include_directories(${SDK_API_COMMON} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${SDK_API_COMMON} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${SDK_API_COMMON} PRIVATE gcov)
endif ()
