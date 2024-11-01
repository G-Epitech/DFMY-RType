target_sources(${SERVER_CORE_LIB} PRIVATE
        level_manager.cpp
        level_manager.hpp
)

add_subdirectory(loader)
add_subdirectory(enemy_spawner)
