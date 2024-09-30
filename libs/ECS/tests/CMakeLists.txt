add_executable(r-type_ECS_sdk_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(r-type_ECS_sdk_tests PRIVATE
        GTest::gtest
        GTest::gtest_main
        r-type_ECS_sdk
)

target_sources(r-type_ECS_sdk_tests PRIVATE
        registry_test.cpp
        system_test.cpp
)
