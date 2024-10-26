target_sources(${SERVER_CORE_LIB} PRIVATE
        archetype_manager.hpp
        archetype_manager.cpp
        archetype_keys.hpp
)

add_subdirectory(component_parser)
