set(NETWORK_SDK_TESTS r-type_network_sdk_tests)

add_executable(${NETWORK_SDK_TESTS})

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(${NETWORK_SDK_TESTS} PRIVATE
        GTest::gtest
        GTest::gtest_main
        r-type_network_sdk
)

add_subdirectory(tools)
