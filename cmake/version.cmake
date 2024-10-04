execute_process(COMMAND git describe --tags --abbrev=0 --match v*
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE)

if (GIT_TAG MATCHES "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)$")
    string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\1" CMAKE_PROJECT_VERSION_MAJOR "${GIT_TAG}")
    string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\2" CMAKE_PROJECT_VERSION_MINOR "${GIT_TAG}")
    string(REGEX REPLACE "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\3" CMAKE_PROJECT_VERSION_PATCH "${GIT_TAG}")
else ()
    set(CMAKE_PROJECT_VERSION_MAJOR 0)
    set(CMAKE_PROJECT_VERSION_MINOR 0)
    set(CMAKE_PROJECT_VERSION_PATCH 0)
endif ()

set(CMAKE_PROJECT_VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH})

message(STATUS "Cmake project version: ${CMAKE_PROJECT_VERSION}")
