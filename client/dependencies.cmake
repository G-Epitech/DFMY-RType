# External dependencies
find_package(fmt REQUIRED QUIET)
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE fmt::fmt)
find_package(SFML REQUIRED COMPONENTS graphics system window CONFIG QUIET)
target_link_libraries(${CLIENT_CORE_LIB} PUBLIC sfml-graphics sfml-window sfml-system)

# Internal dependencies
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE r-type_network_sdk)
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE r-type_ECS_sdk)
