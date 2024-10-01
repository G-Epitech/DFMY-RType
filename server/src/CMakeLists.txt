target_sources(${SERVER_CORE_LIB} PRIVATE
        server_types.hpp
        server_types.cpp
)

include_directories()

add_subdirectory(cli)
add_subdirectory(config)
add_subdirectory(app)
