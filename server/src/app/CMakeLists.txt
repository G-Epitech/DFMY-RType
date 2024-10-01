target_sources(${SERVER_CORE_LIB} PRIVATE
        app.cpp
        app.hpp
        server_interface.hpp
        context.hpp
        context.cpp
)

add_subdirectory(master)
add_subdirectory(lobby)
