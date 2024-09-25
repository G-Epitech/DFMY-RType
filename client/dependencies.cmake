# External dependencies
find_package(fmt REQUIRED)
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE fmt::fmt)
find_package(SFML REQUIRED COMPONENTS graphics system window CONFIG)
target_link_libraries(${CLIENT_CORE_LIB} PUBLIC sfml-graphics sfml-window sfml-system)

# Internal dependencies
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE r-type_network_sdk)
