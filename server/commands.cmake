set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/game_files")
set(DESTINATION_DIR "${CMAKE_BINARY_DIR}/server/game_files")

file(MAKE_DIRECTORY ${DESTINATION_DIR})

add_custom_command(
        TARGET ${SERVER_EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR} ${DESTINATION_DIR}
        COMMENT "Copying directory from ${SOURCE_DIR} to ${DESTINATION_DIR}..."
)

add_custom_target(copy_directory ALL DEPENDS ${SERVER_EXECUTABLE})
