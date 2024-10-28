# External dependencies
find_package(SFML REQUIRED COMPONENTS graphics system window audio CONFIG QUIET)
target_link_libraries(mew PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)

# Internal dependencies
target_link_libraries(mew PUBLIC zygarde)
target_link_libraries(mew PUBLIC porygon)
