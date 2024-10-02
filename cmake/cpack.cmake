set(CPACK_PACKAGE_NAME "R-Type")
set(CPACK_PACKAGE_DESCRIPTION "A game engine that roars!")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CMAKE_PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "G-Epitech")

set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "dragos.suceveanu@epitech.eu")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")

set(CPACK_STRIP_FILES "TRUE")

if (WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
    set(DEPENDENCIES
            $<TARGET_RUNTIME_DLLS:r-type_client>
            $<TARGET_RUNTIME_DLLS:r-type_server>
    )

    install(TARGETS r-type_client
            CONFIGURATIONS Release
            DESTINATION .)

    file(GLOB CLIENT_DLLS "${CMAKE_BINARY_DIR}/client/*.dll")
    install(FILES ${CLIENT_DLLS} DESTINATION .)

    install(TARGETS r-type_server
            CONFIGURATIONS Release
            DESTINATION .)

    file(GLOB SERVER_DLLS "${CMAKE_BINARY_DIR}/server/*.dll")
    install(FILES ${SERVER_DLLS} DESTINATION .)

    install(FILES ${DEPENDENCIES} DESTINATION .)

elseif (UNIX)
    set(CPACK_GENERATOR "DEB;TGZ")

    set(CPACK_PACKAGE_EXECUTABLES "r-type_client;R-Type Client" "r-type_server;R-Type Server")

    set(BUILT_BINARIES r-type_server r-type_client)
    set(BUILT_LIBS abra)

    install(TARGETS ${BUILT_BINARIES}
            CONFIGURATIONS Release
            RUNTIME_DEPENDENCIES
            DESTINATION bin)

    install(TARGETS ${BUILT_LIBS}
            CONFIGURATIONS Release
            DESTINATION lib)

endif ()

include(CPack)
