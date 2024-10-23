add_executable(porygon_tests)

target_sources(porygon_tests PRIVATE
        tests_handler.cpp
)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(porygon_tests PRIVATE
        GTest::gtest
        GTest::gtest_main
        porygon
)

