add_subdirectory(tools)
add_subdirectory(client)
add_subdirectory(server)

target_sources(abra PRIVATE
        core.hpp
)
