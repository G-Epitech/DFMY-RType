target_sources(${SERVER_CORE_LIB} PRIVATE
        cli_handler_interface.hpp
        abstract/cli_handler_abstract.cpp
        abstract/cli_handler_abstract.hpp
        room/cli_handler_room.cpp
        room/cli_handler_room.hpp
        master/cli_handler_master.cpp
        master/cli_handler_master.hpp
        node/cli_handler_node.cpp
        node/cli_handler_node.hpp
        cli_handlers.hpp
)
