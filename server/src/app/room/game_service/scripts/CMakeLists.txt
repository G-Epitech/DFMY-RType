target_sources(${SERVER_CORE_LIB} PRIVATE
        player_script.cpp
        player_script.hpp
        scripts_registry.cpp
        scripts_registry.hpp
)

add_subdirectory(projectiles)
add_subdirectory(enemies)
add_subdirectory(base)
add_subdirectory(helpers)
