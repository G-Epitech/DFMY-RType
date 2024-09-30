add_executable(r-type_network_sdk_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(r-type_network_sdk_tests PRIVATE
  GTest::gtest
  GTest::gtest_main
    r-type_network_sdk
)

add_subdirectory(utils)
