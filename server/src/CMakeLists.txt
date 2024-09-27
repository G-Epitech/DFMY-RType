target_sources(${SERVER_CORE_LIB} PRIVATE
        server_types.hpp
        server_types.cpp
)

add_subdirectory(options)
add_subdirectory(env)
