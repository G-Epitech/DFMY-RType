add_executable(zygarde_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(zygarde_tests PRIVATE
        GTest::gtest
        GTest::gtest_main
        zygarde
)

target_sources(zygarde_tests PRIVATE
        registry_test.cpp
        system_test.cpp
)

add_subdirectory(physics)
