add_library(mew SHARED)

target_include_directories(mew PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(mew PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../..)
target_include_directories(mew PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -framework AudioToolbox -framework CoreAudio"
    )
    target_link_libraries(mew PUBLIC "-framework AudioToolbox" "-framework CoreAudio")
endif ()

include(dependencies.cmake)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(include)

if (COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    target_link_libraries(mew PRIVATE gcov)
endif ()
