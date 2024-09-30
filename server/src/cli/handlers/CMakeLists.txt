target_sources(${SERVER_CORE_LIB} PRIVATE
        cli_handler_interface.hpp
        abstract/cli_handler_abstract.cpp
        abstract/cli_handler_abstract.hpp
        lobby/cli_handler_lobby.cpp
        lobby/cli_handler_lobby.hpp
        master/cli_handler_master.cpp
        master/cli_handler_master.hpp
        cli_handlers.hpp
)