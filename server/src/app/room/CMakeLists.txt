add_subdirectory(game_service)

target_sources(${SERVER_CORE_LIB} PRIVATE
        room.hpp
        room.cpp
        props.hpp
        props.cpp
)
