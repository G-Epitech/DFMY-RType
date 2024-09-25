target_sources(${SERVER_CORE_LIB} PRIVATE
        options_handler_interface.hpp
        abstract/options_handler_abstract.cpp
        abstract/options_handler_abstract.hpp
        lobby/options_handler_lobby.cpp
        lobby/options_handler_lobby.hpp
        allocator/options_handler_allocator.cpp
        allocator/options_handler_allocator.hpp
        option_handlers.hpp
)