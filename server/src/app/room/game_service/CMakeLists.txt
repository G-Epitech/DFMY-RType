target_include_directories(${SERVER_CORE_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${SERVER_CORE_LIB} PRIVATE
        game_service.cpp
        game_service.hpp
        archetype_keys.hpp
)

add_subdirectory(ticks)
add_subdirectory(scripts)
add_subdirectory(level_manager)
add_subdirectory(types)
add_subdirectory(utils)
add_subdirectory(difficulty_loader)
add_subdirectory(player_spawner)
add_subdirectory(network)
