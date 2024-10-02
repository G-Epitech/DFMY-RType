set(SDK_GAME_STATS r-type_game_stats_sdk)

add_library(${SDK_GAME_STATS} SHARED)

add_subdirectory(src)

target_include_directories(${SDK_GAME_STATS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${SDK_GAME_STATS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${SDK_GAME_STATS} PRIVATE gcov)
endif ()
