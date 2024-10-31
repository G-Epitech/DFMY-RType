add_executable(game_tests)

enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/../src/)

find_package(GTest REQUIRED)
target_link_libraries(game_tests PRIVATE
  GTest::gtest
  GTest::gtest_main
  ${GAME_SDK}
)

target_sources(game_tests PRIVATE
  master_test.cpp
)

if (WIN32)
  file(GLOB_RECURSE DLLS "${CMAKE_CURRENT_BINARY_DIR}/../../../libs/**/*.dll")
  add_custom_command(
          TARGET game_tests POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E echo "DLLs found: ${DLLS}"
  )

  foreach(DLL ${DLLS})
    add_custom_command(
            TARGET game_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:game_tests>
    )
  endforeach()
endif ()
