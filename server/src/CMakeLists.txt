target_sources(${SERVER_CORE_LIB} PRIVATE
        server_types.hpp
        server_types.cpp
)

include_directories()

add_subdirectory(cli)
add_subdirectory(env)
add_subdirectory(apps)
