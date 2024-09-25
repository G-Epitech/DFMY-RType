# External dependencies
find_package(fmt REQUIRED QUIET)
target_link_libraries(${SERVER_CORE_LIB} PRIVATE fmt::fmt)

# Internal dependencies
target_link_libraries(${SERVER_CORE_LIB} PRIVATE r-type_network_sdk)
