target_sources(${SERVER_CORE_LIB} PRIVATE
        lobby.hpp
        lobby.cpp
        props.hpp
        props.cpp
        filepaths.hpp
)

add_subdirectory(game_service)
