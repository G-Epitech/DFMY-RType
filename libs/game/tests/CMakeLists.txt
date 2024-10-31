add_executable(game_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(game_tests PRIVATE
  GTest::gtest
  GTest::gtest_main ${GAME_SDK}
)

target_sources(game_tests PRIVATE
  master_test.cpp
)

