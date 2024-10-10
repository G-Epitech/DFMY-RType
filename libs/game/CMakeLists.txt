set(GAME_SDK ${CMAKE_PROJECT_NAME}_game_sdk)

add_library(${GAME_SDK} SHARED)

add_subdirectory(src)
add_subdirectory(includes)

target_include_directories(${GAME_SDK} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(${GAME_SDK} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../..)
target_include_directories(${GAME_SDK} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../)

include(dependencies.cmake)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(${GAME_SDK} PRIVATE gcov)
endif ()
