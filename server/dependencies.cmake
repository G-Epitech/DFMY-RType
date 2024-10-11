# External dependencies
find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(${SERVER_CORE_LIB} PUBLIC Boost::program_options)

# Internal dependencies
target_link_libraries(${SERVER_CORE_LIB} PUBLIC r-type_game_sdk)
target_link_libraries(${SERVER_CORE_LIB} PRIVATE zygarde)
