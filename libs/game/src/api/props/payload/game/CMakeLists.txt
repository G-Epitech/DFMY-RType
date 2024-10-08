add_subdirectory(combat)
add_subdirectory(state)
add_subdirectory(lifecycle)
add_subdirectory(movement)

target_sources(${GAME_SDK} PRIVATE
        game.hpp
)
