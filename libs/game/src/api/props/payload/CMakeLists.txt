target_sources(${GAME_SDK} PRIVATE
        payload.hpp
)

add_subdirectory(game)
add_subdirectory(infos)
add_subdirectory(room)
add_subdirectory(register)
add_subdirectory(player)
add_subdirectory(message)
