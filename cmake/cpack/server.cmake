option(INSTALL_SERVER "Install the server version" OFF)

if (INSTALL_SERVER)

    set(CPACK_PACKAGE_NAME "R-Type")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-server-${CMAKE_PROJECT_VERSION}")

    if (WIN32)

        include(${CMAKE_SOURCE_DIR}/cmake/cpack/windows/server.cmake)

    elseif (UNIX)

        include(${CMAKE_SOURCE_DIR}/cmake/cpack/unix/server.cmake)

    endif ()

    include(${CMAKE_SOURCE_DIR}/cmake/cpack/base.cmake)

endif ()
