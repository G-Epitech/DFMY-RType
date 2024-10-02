add_executable(abra_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(abra_tests PRIVATE
  GTest::gtest
  GTest::gtest_main
    abra
)

add_subdirectory(tools)
