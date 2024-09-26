add_subdirectory(tools)

target_sources(r-type_ECS_sdk PRIVATE
        api.hpp
        entity.hpp
        entity.cpp
        registry.hpp
        registry.tpp
        registry.cpp
)
