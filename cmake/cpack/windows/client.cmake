set(CPACK_GENERATOR "ZIP;NSIS")
set(DEPENDENCIES
        $<TARGET_RUNTIME_DLLS:r-type_client>
)

install(TARGETS r-type_client
        CONFIGURATIONS Release
        DESTINATION bin)

file(GLOB CLIENT_DLLS "${CMAKE_BINARY_DIR}/client/*.dll")
install(FILES ${CLIENT_DLLS} DESTINATION bin)

install(FILES ${DEPENDENCIES} DESTINATION bin)
