set(ClIENT_TESTS r-type_client_tests)

add_executable(${ClIENT_TESTS})

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(${ClIENT_TESTS} PRIVATE
        GTest::gtest
        GTest::gtest_main
        ${CLIENT_CORE_LIB}
)

add_subdirectory(utils)
