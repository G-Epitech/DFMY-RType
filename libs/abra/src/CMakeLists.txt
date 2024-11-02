add_subdirectory(tools)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(database)

target_sources(abra PRIVATE
        core.hpp
)
