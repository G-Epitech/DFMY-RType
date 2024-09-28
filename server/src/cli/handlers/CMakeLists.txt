target_sources(${SERVER_CORE_LIB} PRIVATE
        cli_handler_interface.hpp
        abstract/cli_handler_abstract.cpp
        abstract/cli_handler_abstract.hpp
        lobby/cli_handler_lobby.cpp
        lobby/cli_handler_lobby.hpp
        allocator/cli_handler_allocator.cpp
        allocator/cli_handler_allocator.hpp
        cli_handlers.hpp
)