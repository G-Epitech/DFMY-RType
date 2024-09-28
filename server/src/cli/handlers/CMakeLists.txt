target_sources(${SERVER_CORE_LIB} PRIVATE
        cli_handler_interface.hpp
        abstract/cli_handler_abstract.cpp
        abstract/cli_handler_abstract.hpp
        lobby/cli_handler_lobby.cpp
        lobby/cli_handler_lobby.hpp
        director/cli_handler_director.cpp
        director/cli_handler_director.hpp
        cli_handlers.hpp
)