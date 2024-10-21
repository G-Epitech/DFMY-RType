add_executable(mew_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(mew_tests PRIVATE
        GTest::gtest
        GTest::gtest_main
        mew
)

target_sources(mew_tests PRIVATE
    tests.cpp
)
