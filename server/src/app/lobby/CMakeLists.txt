add_subdirectory(game_service)

target_sources(${SERVER_CORE_LIB} PRIVATE
        lobby.hpp
        lobby.cpp
        props.hpp
        props.cpp
)
