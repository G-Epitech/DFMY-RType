target_sources(${SERVER_CORE_LIB} PRIVATE
        archetype_manager.hpp
        archetype_manager.cpp
)

add_subdirectory(component_parser)
