target_sources(zygarde PRIVATE
        archetype_manager.cpp
        archetype_manager.hpp
)

add_subdirectory(archetype_loader)
add_subdirectory(component_parser)
