add_subdirectory(tools)
add_subdirectory(physics)
add_subdirectory(core)
add_subdirectory(utils)
add_subdirectory(scripting)

target_sources(zygarde PRIVATE
        api.hpp
        entity.hpp
        entity.cpp
        registry.hpp
        registry.tpp
        registry.cpp
        system_abstract.hpp
        system_abstract.tpp
        system_interface.hpp
)
