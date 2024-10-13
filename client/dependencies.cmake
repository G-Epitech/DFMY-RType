# External dependencies
find_package(SFML REQUIRED COMPONENTS graphics system window audio CONFIG QUIET)
target_link_libraries(${CLIENT_CORE_LIB} PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)

# Internal dependencies
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE abra)
target_link_libraries(${CLIENT_CORE_LIB} PRIVATE zygarde)
