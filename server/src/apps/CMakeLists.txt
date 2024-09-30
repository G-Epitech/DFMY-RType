target_sources(${SERVER_CORE_LIB} PRIVATE
        runner.cpp
        runner.hpp
        server_interface.hpp
        context.hpp
)

add_subdirectory(master)
add_subdirectory(lobby)
