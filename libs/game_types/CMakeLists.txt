set(SDK_GAME_TYPES r-type_game_types_sdk)

add_library(${SDK_GAME_TYPES} SHARED)

add_subdirectory(src)

target_include_directories(${SDK_GAME_TYPES} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${SDK_GAME_TYPES} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${SDK_GAME_TYPES} PRIVATE gcov)
endif ()
