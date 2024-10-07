option(INSTALL_CLIENT "Install the client version" OFF)

if (INSTALL_CLIENT)
    set(CPACK_PACKAGE_NAME "R-Type")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-client-${CMAKE_PROJECT_VERSION}")
    set(CPACK_PACKAGE_EXECUTABLES "r-type_client;R-Type")

    if (WIN32)

        include(${CMAKE_SOURCE_DIR}/cmake/cpack/windows/client.cmake)

    elseif (UNIX)

        include(${CMAKE_SOURCE_DIR}/cmake/cpack/unix/client.cmake)

    endif ()

    include(${CMAKE_SOURCE_DIR}/cmake/cpack/base.cmake)

endif ()
