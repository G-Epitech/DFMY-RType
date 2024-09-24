# External dependencies
find_package(fmt REQUIRED QUIET)
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE fmt::fmt)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED QUIET)
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE sfml-graphics sfml-window sfml-system)

# Internal dependencies
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE r-type_network_sdk)
