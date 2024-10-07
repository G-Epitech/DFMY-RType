add_subdirectory(tools)

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
