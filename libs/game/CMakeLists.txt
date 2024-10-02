set(SDK_GAME r-type_game_core_sdk)

add_library(${SDK_GAME} SHARED)

add_subdirectory(src)

target_include_directories(${SDK_GAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${SDK_GAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${SDK_GAME} PRIVATE gcov)
endif ()
