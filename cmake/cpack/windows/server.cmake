set(CPACK_GENERATOR "ZIP;NSIS")
set(DEPENDENCIES
        $<TARGET_RUNTIME_DLLS:r-type_server>
)

install(TARGETS r-type_server
        CONFIGURATIONS Release
        DESTINATION bin)

file(GLOB SERVER_DLLS "${CMAKE_BINARY_DIR}/server/*.dll")
install(FILES ${SERVER_DLLS} DESTINATION bin)

install(FILES ${DEPENDENCIES} DESTINATION bin)
