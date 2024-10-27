target_sources(${SERVER_CORE_LIB} PRIVATE
        game_service.cpp
        game_service.hpp
        archetype_keys.hpp
)

add_subdirectory(ticks)
add_subdirectory(factories)
add_subdirectory(enemy_manager)
add_subdirectory(state_broadcaster)
add_subdirectory(scripts)
