set(SERVER_TESTS r-type_server_tests)

add_executable(${SERVER_TESTS})

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(${SERVER_TESTS} PRIVATE
        GTest::gtest
        GTest::gtest_main
        ${SERVER_CORE_LIB}
)

add_subdirectory(utils)
